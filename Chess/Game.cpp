#include <iostream>
#include <SDL.h>

#include "Utils.h"
#include "AllChessPieces.h"
#include "Game.h"

using namespace std;


const int maxNumPawns		= 8;
const int maxNumMiddlePieces= 2;

//const int GAME_FPS			= 60;
//const int CANVAS_WIDTH		= 800;
//const int CANVAS_HEIGHT		= 800;
//const int horizontalSquares = 8;
//const int verticalSquares	= 8;
//string IMG_PIECES_DIR		= "images/pieces/";;
//string IMG_BOARDS_DIR		= "images/boards/";;
//
//ostream& operator<< (ostream& out, const SDL_Rect* rec) {
//	if (rec == nullptr) {
//		out << "NULLPTR";
//		return out;
//	}
//	out << "[" << rec->x << "," << rec->y << "," << rec->w << "," << rec->h << "]";
//	return out;
//}
//
//ostream& operator<< (ostream& out, const PieceColor color) {
//
//	switch (color) {
//	case PieceColor::WHITE:
//		out << "WHITE";
//		break;
//	case PieceColor::BLACK:
//		out << "BLACK";
//		break;
//	case PieceColor::NONE:
//		out << "NONE";
//		break;
//	default:
//		break;
//	}
//	return out;
//}

Game::Game(bool closeGame, SDL_Renderer *rend, SDL_Window *window) 
:	closeGame(closeGame), rend(rend), window(window), 
	windowTexture(nullptr), currClickedPiece(nullptr),
	colorTurn(PieceColor::WHITE), mouseIsPressed(false),
	showLegalMoves(false) {
	
	///* Board */
	board = new Board();

	///* Pieces */
	for (int i = 0; i < 8; i++) {
		allPieces.push_back(new Pawn (PieceColor::WHITE, "White Pawn"    + to_string(i)));
		allPieces.push_back(new Pawn (PieceColor::BLACK, "Black Pawn"    + to_string(i)));
	}
	for (int i = 0; i < 2; i++) {
		allPieces.push_back(new Bishop(PieceColor::WHITE, "White Bishop" + to_string(i)));
		allPieces.push_back(new Bishop(PieceColor::BLACK, "Black Bishop" + to_string(i)));
		
		allPieces.push_back(new Knight(PieceColor::WHITE, "White Knight" + to_string(i)));
		allPieces.push_back(new Knight(PieceColor::BLACK, "Black Knight" + to_string(i)));
		
		allPieces.push_back(new Rook  (PieceColor::WHITE, "White Rook"   + to_string(i)));
		allPieces.push_back(new Rook  (PieceColor::BLACK, "Black Rook"   + to_string(i)));
	}

	allPieces.push_back(new Queen(PieceColor::WHITE, "White Queen"));
	allPieces.push_back(new Queen(PieceColor::BLACK, "Black Queen"));

	allPieces.push_back(new King(PieceColor::WHITE, "White King"));
	allPieces.push_back(new King(PieceColor::BLACK, "Black King"));
}

Game::~Game() {

	delete currClickedPiece;
	SDL_DestroyTexture(windowTexture);

	// destroy renderer
	SDL_DestroyRenderer(rend);
	// destroy window
	SDL_DestroyWindow(window);
	// closeGame SDL
	SDL_Quit();
}

void Game::init() {
	
	gameSDL_init();
	renderAllElements();
}

void Game::gameSDL_init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
	}

	window = SDL_CreateWindow("Chess - by Thiago Lages (@thiagolages)",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CANVAS_WIDTH, CANVAS_HEIGHT, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		SDL_Quit();
	}
	// triggers the program that controls your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	rend = SDL_CreateRenderer(window, -1, render_flags);

}

void Game::renderAll() {
	
	SDL_RenderClear(rend);
	render(board);

	renderAllElements();
	renderLegalMoves();
	if (currClickedPiece) {
		render(currClickedPiece); // make clicked piece appear on top of all others
	}
	show();
}

void Game::renderAllElements() {
	for (auto piece : allPieces) {
		render(piece);
	}
}

void Game::show() {
	SDL_RenderPresent(rend);
}

void Game::renderLegalMoves() {

	if (showLegalMoves) {
		for (auto& move : legalMoves) {
			renderCircle(move);
		}
	}
}

void Game::calcLegalMoves(Piece* piece) {

	vector<Position> moves = piece->calcMoves();
	for (auto &move : moves) {
		if (isLegalMove(piece, move)) {
			legalMoves.push_back(move);
			showLegalMoves = true;
		}
	}
	// do the same for capture moves, if different
	if (instanceof<Pawn>(piece)) {
		moves = piece->calcCaptures();
		for (auto& move : moves) {
			if (isLegalMove(piece, move)) {
				legalMoves.push_back(move);
				showLegalMoves = true;
			}
		}
	}
}

void Game::clearLegalMoves() {
	showLegalMoves = false;
	legalMoves.clear();
}

void Game::renderCircle(Position boardPos, int radius) {
	
	if (boardPos.x < 0 || boardPos.x > horizontalSquares
	 || boardPos.y < 0 || boardPos.y > verticalSquares) {
		cout << "can't render position " << boardPos << endl;
		return;
	}

	// convert position to pixels and adjust for the center of the square
	Position posInPixels(boardPos.x * Piece::pieceSize.w + Piece::pieceSize.w / 2,
		boardPos.y * Piece::pieceSize.h + Piece::pieceSize.h / 2);

	drawCircle(posInPixels, radius);
	
}

void Game::render(ChessElement* ce) {

	if (ce->hasBeenCaptured) {
		return;
	}
	
	// REALLY IMPORTANT !! deallocate texture before assigning it to another one
	SDL_DestroyTexture(ce->texture);
	ce->texture = IMG_LoadTexture(rend, ce->imgFilename.c_str());
	
	// enhance the quality of the texture
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (ce->texture == NULL) {
		std::cout << "couldnt create texture from surface " << std::endl;
		cout << IMG_GetError() << endl;
		return;
	}

	SDL_RenderCopy(rend, ce->texture, ce->srcRect, ce->dstRect);
}

void Game::drawCircle(Position centerInPixels, int radius){
	
	Position center = pixelPosToBoardPos(centerInPixels);
	PieceColor squareColor = (center.x + center.y) % 2 == 0 ? PieceColor::WHITE : PieceColor::BLACK;
	string circleFilename = squareColor == PieceColor::WHITE ? IMG_CIRCLES_DIR+"circle_white_square.png" : IMG_CIRCLES_DIR + "circle_black_square.png";
	SDL_Texture* text = IMG_LoadTexture(rend, circleFilename.c_str());
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (text == NULL) {
		std::cout << "couldnt create texture from surface " << std::endl;
		SDL_DestroyTexture(text);
		cout << IMG_GetError() << endl;
		return;
	}

	SDL_Rect* srcRect = nullptr;
	SDL_Rect* dstRect = new SDL_Rect{
		centerInPixels.x - Piece::pieceSize.w / 2,
		centerInPixels.y - Piece::pieceSize.h / 2,
		Piece::pieceSize.w,
		Piece::pieceSize.h
	};
	SDL_RenderCopy(rend, text, srcRect, dstRect);

	SDL_DestroyTexture(text);
	delete srcRect;
	delete dstRect;

	return;

	// https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
	//int centreX = centerInPixels.x;
	//int centreY = centerInPixels.y;

	//const int diameter = (radius * 2);

	//int x = (radius - 1);
	//int y = 0;
	//int tx = 1;
	//int ty = 1;
	//int error = (tx - diameter);

	//while (x >= y)
	//{
	//	//  Each of the following renders an octant of the circle
	//	SDL_RenderDrawPoint(rend, centreX + x, centreY - y);
	//	SDL_RenderDrawPoint(rend, centreX + x, centreY + y);
	//	SDL_RenderDrawPoint(rend, centreX - x, centreY - y);
	//	SDL_RenderDrawPoint(rend, centreX - x, centreY + y);
	//	SDL_RenderDrawPoint(rend, centreX + y, centreY - x);
	//	SDL_RenderDrawPoint(rend, centreX + y, centreY + x);
	//	SDL_RenderDrawPoint(rend, centreX - y, centreY - x);
	//	SDL_RenderDrawPoint(rend, centreX - y, centreY + x);

	//	if (error <= 0)
	//	{
	//		++y;
	//		error += ty;
	//		ty += 2;
	//	}

	//	if (error > 0)
	//	{
	//		--x;
	//		tx += 2;
	//		error += (tx - diameter);
	//	}
	//}
}

void Game::reset() {
	for (auto piece : allPieces) {
		piece->setCurrPosInBoard(piece->getInitialPosInBoard());
		piece->hasBeenCaptured  = false;
		piece->hasBeenMovedOnce = false;
	}
	colorTurn = PieceColor::WHITE;
}

Piece* Game::pixelPosToPiece(const Position pos) {
	return (pixelPosToPiece(pos.x, pos.y));
}

Piece* Game::pixelPosToPiece(const int& xPosInPixels, const int& yPosInPixels) {

	Position boardPos = Position(xPosInPixels / Piece::pieceSize.w, 
								   yPosInPixels / Piece::pieceSize.w);
	
	return (boardPosToPiece(boardPos));
}

Piece* Game::boardPosToPiece(const Position boardPos) {

	for (auto e : allPieces) {
		if (boardPos == e->getCurrPosInBoard()) {
			return e;
		}
	}
	// if nothing is found
	return nullptr;
}

void Game::handleEvents(SDL_Event& event) {
	switch (event.type) {
	case SDL_QUIT: // handling of closeGame button
		this->closeGame = true;
		break;
	case SDL_KEYDOWN:
		this->handleKeyDown(event);
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			this->mouseIsPressed = true;
			this->handleMouseButtonDown(event);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		this->mouseIsPressed = false;
		this->handleMouseButtonUp(event);
		break;
	case SDL_MOUSEMOTION:
		this->handleMouseMotion(event);
		break;
	}// end switch event type
}

void Game::handleKeyDown(SDL_Event& event) {
	switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_ESCAPE:
			this->closeGame = true;
			break;
		case SDL_SCANCODE_Q:
			this->closeGame = true;
			break;
		case SDL_SCANCODE_R:
			reset();
			break;
	}// end switch key scancode
}

void Game::handleMouseButtonDown(SDL_Event& event) {

	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);

	//Piece* auxClickedPiece = pixelPosToPiece(xPosInPixels, yPosInPixels);

	currClickedPiece = pixelPosToPiece(xPosInPixels, yPosInPixels);

	//only allow current color to be played
	if (!isYourTurn()) {
		currClickedPiece = nullptr;
		clearLegalMoves();
	}
	if (currClickedPiece) {
		// if we're already showing, means we clicked again and we want to remove all legal moves from the screen
		if (showLegalMoves) {
			clearLegalMoves();
			return;
		}
		calcLegalMoves(currClickedPiece);
	}
	else {
		clearLegalMoves();
	}
}

void Game::handleMouseMotion(SDL_Event& event) {

	if (currClickedPiece == nullptr) {
		return;
	}

	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);

	// center the image in the mouse position
	xPosInPixels -= Piece::pieceSize.w / 2;
	yPosInPixels -= Piece::pieceSize.h / 2;
	Position posInPixels = { xPosInPixels, yPosInPixels };

	// IMPORTANT: we must not update position in board until piece is finally placed, thus, using 'false' for update
	currClickedPiece->setCurrPosInPixels(posInPixels, false);
	render(currClickedPiece);
}

void Game::handleMouseButtonUp(SDL_Event& event) {

	if (currClickedPiece == nullptr) {
		return;
	}

	bool shouldChangeTurns = true; // auxiliary to change turns or not

	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);
	Position posInPixels = { xPosInPixels, yPosInPixels };
	Position boardPos  = pixelPosToBoardPos(posInPixels);

	Piece* targetPiece = pixelPosToPiece(posInPixels);
	if (targetPiece) {
		cout << "target piece is " << targetPiece->getName() << endl;
	}else{ cout << "target piece is nullptr"<< endl; }
	
	cout << "pixelPos before isLegalMove" << posInPixels << endl;
	cout << "boardPos before isLegalMove" << boardPos << endl;
	// check legal moves
	if (!isLegalMove(currClickedPiece, boardPos)) {
		// must render back to original position
		currClickedPiece->setCurrPosInBoard(currClickedPiece->getCurrPosInBoard());// return to the same position it was in the board
		shouldChangeTurns = false; // nothing really happened, so don't change turns
		currClickedPiece = nullptr;
		targetPiece = nullptr;
		delete targetPiece;
		// and then return
		return;
	}

	// if nothing in the square
	if (targetPiece == nullptr ) {
		// move
		currClickedPiece->setCurrPosInBoard(boardPos);
		currClickedPiece->hasBeenMovedOnce = true;
	}
	else { // check capture or not
		if (isDifferentColor(currClickedPiece, targetPiece) && pieceCanMakeCaptureMove(currClickedPiece, boardPos)) {
			// capture
			cout << "different color pieces" << endl;
			targetPiece->capturedPieceRoutine();
			currClickedPiece->setCurrPosInBoard(boardPos);
			currClickedPiece->hasBeenMovedOnce = true;
	}
		else { 
			// not a capture
			cout << "same color pieces" << endl;			
			currClickedPiece->setCurrPosInBoard(currClickedPiece->getCurrPosInBoard());// return to the same position it was in the board
			shouldChangeTurns = false; // nothing really happened, so don't change turns
		}
	}

	currClickedPiece = nullptr;
	targetPiece = nullptr;
	delete targetPiece;

	clearLegalMoves(); // stop showing legal moves on the screen

	// change turns;
	if (shouldChangeTurns) {
		changeTurns();
	}
}

void Game::changeTurns() {
	this->colorTurn = (this->colorTurn == PieceColor::WHITE ? PieceColor::BLACK : PieceColor::WHITE);
}

bool Game::isYourTurn() {
	if (currClickedPiece == nullptr) { return false; }
	return (currClickedPiece->getColor() == this->colorTurn);
}

bool Game::isDifferentColor(Piece* p1, Piece* p2) {
	return (p1->getColor() != p2->getColor());
}

bool Game::isDifferentPiece(Piece* p1, Piece* p2){
	return (p1 != p2);
}

bool Game::isInSameDiagonal(Position p1, Position p2) {
	return (abs(p1.x - p2.x) == abs(p1.y - p2.y));
}

bool Game::isInSameColumn(Position p1, Position p2) {
	return (p1.x == p2.x);
}

bool Game::isInSameRow(Position p1, Position p2) {
	return (p1.y == p2.y);
}

bool Game::isLegalMove(Piece* piece, Position boardPos) {

	if (!isWithinBoardLimits(boardPos)) {
		cout << "Position in board " << boardPos << " outside board limits" << endl;
		return false;
	}
	cout << "isWithinBoardLimits" << endl;

	cout << "boardPos before piececanmakemove = " << boardPos << endl;
	// piece has to be able to move to that position
	if (!pieceCanMakeMove(piece, boardPos) && !pieceCanMakeCaptureMove(piece, boardPos)) { cout << piece->getName() << " can't make move." << endl; return false; }
	cout << "pieceCanMakeMove" << endl;

	// make sure no piece is in front of the squares we're moving throught, except for the knight
	if (theresAPieceBetween(piece, boardPos)) { cout << "There's a piece between." << endl; return false; }
	cout << "theres NOT APieceBetween, so we're OK" << endl;

	// verify if my own king wont be in check after I move
	if (!isKingSafeAfterMove(piece, boardPos)) { cout << piece->getColor() << " King is not safe if you make that move." << endl; return false; }
	cout << "isKingSafeAfterMove" << endl;

	// if there's no piece in the way
	if (!theresAPieceIn(boardPos)) { cout << "There's NOT a piece in " << boardPos << endl; return true; }
	cout << "there IS APieceIn the final position. Let's check if it's a capture or illegal move" << endl;

	// if there's a piece in the way, but it is of the same color, we cant move
	Piece* auxPiece = boardPosToPiece(boardPos);

	if (auxPiece->getColor() == piece->getColor()) {
		cout << "piece of the same color, cant move!" << endl;
		auxPiece = nullptr;
		delete auxPiece;
		return false;
	}

	auxPiece = nullptr;
	delete auxPiece;

	// if nothing else returned, means we have an enemy piece. let's check if we are able to capture it or not
	if (pieceCanMakeCaptureMove(currClickedPiece, boardPos)) {
		return true;
	} else {
		return false;
	}
		
}

bool Game::pieceCanMakeMove(Piece* piece, Position boardPos) {
	for (auto& move : piece->calcMoves()) {
		if (move == boardPos) {
			return true;
		}
	}
	// if we didn't return true before, we can't reach that position
	return false;
}

bool Game::pieceCanMakeCaptureMove(Piece* piece, Position boardPos) {
	cout << "calculatig ";
	Piece* auxPiece = nullptr;
	for (auto& move : piece->calcCaptures()) {
		
		cout << move << endl;
		auxPiece = boardPosToPiece(move);
		if (auxPiece == nullptr) {
			continue;
		}
		// if there is a enemy piece in that direction
		if (move == boardPos 
			&& auxPiece->getCurrPosInBoard() == boardPos
			&& auxPiece->getColor() != piece->getColor()) {
			cout << "returning true" << endl;
			auxPiece = nullptr;
			delete auxPiece;
			return true;
		}
	}
	// if we didn't return true before, we can't reach that position
	cout << "returning false" << endl;
	auxPiece = nullptr;
	delete auxPiece;
	return false;
}

bool Game::theresAPieceIn(Position boardPos) {
	
	Piece*   auxPiece  = boardPosToPiece(boardPos);
	bool		answer = (auxPiece == nullptr ? false : true);
	
	auxPiece = nullptr;
	delete auxPiece;
	
	return answer;
}

bool Game::theresAPieceBetween(Piece* piece, Position dstPos) {
	
	vector<Position> positionsInBetween;
	Position piecePos = piece->getCurrPosInBoard();
	
	// if in same file (column) (x coord)
	if (isInSameColumn(piecePos, dstPos)) {
		int initialYPos = min(piecePos.y, dstPos.y) + 1; // adding 1 so we dont include the current y value (since we're looking for in-between squares)
		int finalYPos   = max(piecePos.y, dstPos.y);
		
		if (finalYPos <= initialYPos) { return false; } // squares are adjacent

		finalYPos -= 1; // subtrc 1 so we dont include the current y value (since we're looking for in-between squares)

		for (int ypos = initialYPos; ypos <= finalYPos; ypos++) {
			positionsInBetween.push_back(Position(piecePos.x, ypos));
		}
	}
	// if in same row (y coord)
	else if (isInSameRow(piecePos, dstPos)) {
		int initialXPos = min(piecePos.x, dstPos.x) + 1; // adding 1 so we dont include the current y value (since we're looking for in-between squares)
		int finalXPos	= max(piecePos.x, dstPos.x);

		if (finalXPos <= initialXPos) { return false; } // squares are adjacent

		finalXPos -= 1; // subtrc 1 so we dont include the current y value (since we're looking for in-between squares)

		for (int xpos = initialXPos; xpos <= finalXPos; xpos++) {
			positionsInBetween.push_back(Position(xpos, piecePos.y));
		}
	}// if in same diagonal
	else if (isInSameDiagonal(piecePos, dstPos)) {
		int xIncr = (piecePos.x < dstPos.x ? 1 : -1);
		int yIncr = (piecePos.y < dstPos.y ? 1 : -1);

		Position auxPos = piecePos;
		auxPos.x += xIncr;
		auxPos.y += yIncr;

		if (auxPos == dstPos) { return false; } // squares are adjacent

		Position auxFinalPos = dstPos;
		auxFinalPos.x -= xIncr;
		auxFinalPos.y -= yIncr;
		
		// at least this square is in between
		positionsInBetween.push_back(auxPos);

		while (auxPos != auxFinalPos) {	// while we haven't reached the last square in between
			auxPos.x += xIncr;
			auxPos.y += yIncr;
			positionsInBetween.push_back(auxPos);
		}
	}
	else {
		// if not in same row, column or diag, either knight move or illegal (will be checked in other functions)
		cout << "Piece not in the same row, column or diagonal" << endl;
		return false;
	}

	for (auto& pos : positionsInBetween) {
		if (theresAPieceIn(pos)) {
			return true;
		}
	}
	// if there's nothing
	return false;
}

bool  Game::isKingSafeAfterMove(Piece* piece, Position dstPos) {
	
	Position kingPos = Position();
	bool kingFound = false;

	PieceColor pieceColor = piece->getColor();
	for (auto& p : allPieces) {
		if (instanceof<King>(p) && p->getColor() == pieceColor) {
			kingPos = p->getCurrPosInBoard();
			kingFound = true;
			break;
		}
	}

	if (!kingFound) {
		cerr << pieceColor << " King not found ! Can't check for king safety." << endl;
		return false;
	}

	Position piecePos = piece->getCurrPosInBoard();
	
	Position auxPos = kingPos;

	// auxiliaries to iterate on rows, cols or diags
	int dx = 0;
	int dy = 0;

	/* if piece is in same (row/column/diag) and we move it to same (row/column/diag), there is no danger */
	if (isInSameDiagonal(piecePos, kingPos)) {
		if (isInSameDiagonal(dstPos, kingPos)) return true; 
		cout << "testing for pice between " << piece->getName() << " and " << kingPos << endl;
		if (theresAPieceBetween(piece, kingPos)) { cout << "there is a piece !" << endl;return true;}
	}
	else if (isInSameRow(piecePos, kingPos)) {
		if (isInSameRow(dstPos, kingPos)) return true;
		cout << "testing for pice between " << piece->getName() << " and " << kingPos << endl;
		if (theresAPieceBetween(piece, kingPos)) { cout << "there is a piece !" << endl;return true; }
	}
	else if (isInSameColumn(piecePos, kingPos)) {
		if (isInSameColumn(dstPos, kingPos)) return true;
		cout << "testing for pice between " << piece->getName() << " and " << kingPos << endl;
		if (theresAPieceBetween(piece, kingPos)) { cout << "there is a piece !" << endl;return true; }
	}
	else {// if piece is not in same diagonal, row or col, it won't make its own king stay in a check position
		return true;
	}
	/*-------------------------------------------------------------------------------------------------------*/

	Piece* auxPiece = nullptr;

	// check in which diagonal the piece is with respect to the king
	if (isInSameDiagonal(piecePos, kingPos)) {
		dx = (piecePos.x > kingPos.x ? 1 : -1); 
		dy = (piecePos.y > kingPos.y ? 1 : -1);
	}
	else if (isInSameRow(piecePos, kingPos)) {
		dx = (piecePos.x > kingPos.x ? 1 : -1);
		dy = 0;
	}
	else if (isInSameColumn(piecePos, kingPos)) {
		dx = 0;
		dy = (piecePos.y > kingPos.y ? 1 : -1);
	}

	// if we add dx and dy to the king's position (stored in auxPos now), we will check the next square in the same (row/col/diag)
	auxPos.x += dx;
	auxPos.y += dy;

	if (dx == 0 && dy == 0) {
		cerr << "Something went wrong in  Game::isKingSafeAfterMove()" << endl;
		auxPiece = nullptr;
		delete auxPiece;
		return false; 
	}

	while (isWithinBoardLimits(auxPos)) {
		auxPiece = nullptr; // reset it from last iteration
		auxPiece = boardPosToPiece(auxPos);
		if (auxPiece) { // there's a piece

			if (auxPiece == piece) {  // if the selected piece is the same that we're trying to move, continue in the loop
				auxPos.x += dx;
				auxPos.y += dy;
				continue;
			}

			if (auxPiece->getColor() != piece->getColor()) { // there's an enemy piece

				vector<Position> possibleMoves = auxPiece->calcMoves();
				for (auto& move : possibleMoves) {
					if (move == kingPos) {
						// the enemy piece can attack our king
						auxPiece = nullptr;
						delete auxPiece;
						return false;
					}
				}
				// the enemy piece CANNOT attack our king
				auxPiece = nullptr;
				delete auxPiece;
				return true;

			}
			else { // there's a piece of same color

				// if there's one piece between our king and the enemy piece, we're good
				auxPiece = nullptr;
				delete auxPiece;
				return true;
			}
		}
		// go to next iteration
		auxPos.x += dx;
		auxPos.y += dy;
	}

	auxPiece = nullptr;
	delete auxPiece;
	// if we reached the end of the board and havent returned, we're safe
	return true;

}

Position Game::pixelPosToBoardPos(Position pixelPos) {
	return (Position(
		pixelPos.x / Piece::pieceSize.w,
		pixelPos.y / Piece::pieceSize.h
	));
}

Position Game::boardPosToPixelPos(Position boardPos) {
	return (Position(
		boardPos.x * Piece::pieceSize.w,
		boardPos.y * Piece::pieceSize.h
	));
}