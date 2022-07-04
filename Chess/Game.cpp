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
//ostream& operator<< (ostream& out, const ChessElementColor color) {
//
//	switch (color) {
//	case ChessElementColor::WHITE:
//		out << "WHITE";
//		break;
//	case ChessElementColor::BLACK:
//		out << "BLACK";
//		break;
//	case ChessElementColor::NONE:
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
	colorTurn(ChessElementColor::WHITE) {
	
	///* Board */
	board = new Board();

	///* Pieces */
	for (int i = 0; i < 8; i++) {
		allPieces.push_back(new Pawn (ChessElementColor::WHITE, "White Pawn"    + to_string(i)));
		allPieces.push_back(new Pawn (ChessElementColor::BLACK, "Black Pawn"    + to_string(i)));
	}
	for (int i = 0; i < 2; i++) {
		allPieces.push_back(new Bishop(ChessElementColor::WHITE, "White Bishop" + to_string(i)));
		allPieces.push_back(new Bishop(ChessElementColor::BLACK, "Black Bishop" + to_string(i)));
		
		allPieces.push_back(new Knight(ChessElementColor::WHITE, "White Knight" + to_string(i)));
		allPieces.push_back(new Knight(ChessElementColor::BLACK, "Black Knight" + to_string(i)));
		
		allPieces.push_back(new Rook  (ChessElementColor::WHITE, "White Rook"   + to_string(i)));
		allPieces.push_back(new Rook  (ChessElementColor::BLACK, "Black Rook"   + to_string(i)));
	}

	allPieces.push_back(new Queen(ChessElementColor::WHITE, "White Queen"));
	allPieces.push_back(new Queen(ChessElementColor::BLACK, "Black Queen"));

	allPieces.push_back(new King(ChessElementColor::WHITE, "White King"));
	allPieces.push_back(new King(ChessElementColor::BLACK, "Black King"));
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

void Game::renderAllElements() {
	
	// CHANGE THIS SO THAT CHESSELEMENT HAS A VIRTUAL FUNCTION CALLED setCurrPosInPixels
	SDL_RenderClear(rend);
	render(board);

	for (auto piece : allPieces) {
		render(piece);
	}

	// if there's a piece clicked, render it last so it appears on top of everyone else
	if (currClickedPiece) {
		render(currClickedPiece);
	}
	show();
}

void Game::show() {
	SDL_RenderPresent(rend);
}

void Game::renderLegalMoves(Piece* piece) {
	
	vector<Position> positions = piece->calcMoves();
	for (auto &pos : positions) {
		Position finalPos(	piece->getCurrPosInBoard().x + pos.x,
							piece->getCurrPosInBoard().y + pos.y);
		render(finalPos);
	}
}

void Game::render(Position posInBoard) {
	if (posInBoard.x < 0 || posInBoard.x > horizontalSquares
	 || posInBoard.y < 0 || posInBoard.y > verticalSquares) {
		return;
	}
	
	int radius = Piece::pieceSize.w / 4;
	cout << "rendering " << posInBoard << " with radius " << radius << endl;
	// get current piece position to sum with deltas received, and adjust for the center of the square
	Position posInPixels(posInBoard.x * Piece::pieceSize.w + Piece::pieceSize.w / 2,
						 posInBoard.y * Piece::pieceSize.h + Piece::pieceSize.h / 2);
	drawCircle(posInPixels, radius);

	show();

	//SDL_Texture* texture = IMG_LoadTexture(rend, "redSquare.png");

	// enhance the quality of the texture
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	/*if (texture == NULL) {
		std::cout << "couldnt create texture from surface " << std::endl;
		cout << IMG_GetError() << endl;
		return;
	}*/

	/*SDL_Rect* dstRect = new SDL_Rect({ posInBoard.x,
							posInBoard.y,
							Piece::pieceSize.w,
							Piece::pieceSize.h
		});*/

	//SDL_RenderCopy(rend, texture, nullptr, dstRect);

	//delete dstRect;
	//SDL_DestroyTexture(texture);
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

	//delete ce->texture;
}

// https://stackoverflow.com/questions/38334081/howto-draw-circles-arcs-and-vector-graphics-in-sdl
void Game::drawCircle(Position center, int radius){
	
	int centreX = center.x;
	int centreY = center.y;

	const int diameter = (radius * 2);

	int x = (radius - 1);
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(rend, centreX + x, centreY - y);
		SDL_RenderDrawPoint(rend, centreX + x, centreY + y);
		SDL_RenderDrawPoint(rend, centreX - x, centreY - y);
		SDL_RenderDrawPoint(rend, centreX - x, centreY + y);
		SDL_RenderDrawPoint(rend, centreX + y, centreY - x);
		SDL_RenderDrawPoint(rend, centreX + y, centreY + x);
		SDL_RenderDrawPoint(rend, centreX - y, centreY - x);
		SDL_RenderDrawPoint(rend, centreX - y, centreY + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void Game::reset() {
	for (auto piece : allPieces) {
		piece->setCurrPosInBoard(piece->getInitialPosInBoard());
		piece->hasBeenCaptured = false;
	}
}

Piece* Game::pixelPositionToPiece(const int& xPosInPixels, const int& yPosInPixels) {

	Position posInBoard = Position(xPosInPixels / Piece::pieceSize.w, 
								  yPosInPixels / Piece::pieceSize.w);
	for (auto e : allPieces) {
		if (posInBoard == e->getCurrPosInBoard()) {
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
			this->handleMouseButtonDown(event);
		}
		break;
	case SDL_MOUSEBUTTONUP:
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

	currClickedPiece = pixelPositionToPiece(xPosInPixels, yPosInPixels);

	//only allow current color to be played
	if (!isYourTurn()) {
		currClickedPiece = nullptr;
	}
	if (currClickedPiece) {
		renderLegalMoves(currClickedPiece);
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

	cout << "currClickedPiece = " << currClickedPiece->getName() << endl;

	bool shouldChangeTurns = true; // auxiliary to change turns or not

	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);

	Position posInPixels = { xPosInPixels, yPosInPixels };
	Position posInBoard  = { xPosInPixels / Piece::pieceSize.w, yPosInPixels / Piece::pieceSize.h };

	Piece* targetPiece = pixelPositionToPiece(xPosInPixels, yPosInPixels);
	cout << "curr piece is " << currClickedPiece->getName() << endl;
	if (targetPiece) {
		cout << "target piece is " << targetPiece->getName() << endl;
	}else{ cout << "target piece is nullptr"<< endl; }
	
	// check legal moves
	if (!currClickedPiece->isLegalMove(posInBoard)) {
		// must render back to original position
		// and then return
		return;
	}

	// if nothing in the square, or if putting same piece back on it
	if (targetPiece == nullptr ) {
		// put the piece in the square where the mouse stopped
		currClickedPiece->setCurrPosInBoard(posInBoard);
		currClickedPiece->hasBeenMovedOnce = true;
	}
	else {
		// check capture or not
		if (isDifferentColor(currClickedPiece, targetPiece)) {
			// capture
			cout << "different color pieces" << endl;
			targetPiece->capturedPieceRoutine();
			currClickedPiece->setCurrPosInBoard(posInBoard);
			currClickedPiece->hasBeenMovedOnce = true;
		}
		else { // not a capture
			cout << "same color pieces" << endl;
			// return to the same position it was in the board
			currClickedPiece->setCurrPosInBoard(currClickedPiece->getCurrPosInBoard());
			shouldChangeTurns = false; // nothing really happened, so don't change turns
		}
	}

	currClickedPiece = nullptr;
	targetPiece = nullptr;
	delete targetPiece;

	// change turns;
	if (shouldChangeTurns) {
		changeTurns();
	}
}

void Game::changeTurns() {
	this->colorTurn = (this->colorTurn == ChessElementColor::WHITE ? ChessElementColor::BLACK : ChessElementColor::WHITE);
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