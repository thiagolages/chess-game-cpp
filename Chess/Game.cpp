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
	isResetting(false), colorTurn(ChessElementColor::WHITE) {
	
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
		if (this->isResetting) {
			cout << "Rendering " << piece->getName() << " to " << piece->getCurrPosInBoard() << endl;
		}
		render(piece);
	}
	if (this->isResetting) {
		this->isResetting = false;
	}
	show();
}

void Game::show() {
	SDL_RenderPresent(rend);
}

void Game::render(ChessElement* ce) {

	if (ce->hasBeenCaptured) {
		return;
	}

	/**************************************/
	// old way of creating a texture (through a Surface)
	//image_surface = IMG_Load(imgFilename.c_str());

	//if (image_surface == NULL) {
	//	std::cout << "couldnt load " << imgFilename << std::endl;
	//	cout << IMG_GetError() << endl;
	//}
	//// enhance the quality of the texture
	//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//texture = SDL_CreateTextureFromSurface(rend, image_surface);
	/**************************************/

	// new way of creating a texture (no need to use a Surface)
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

void Game::reset() {
	this->isResetting = true;
	for (auto piece : allPieces) {
		//cout << "Resetting " << piece->getName() << " to " << piece->getInitialPosInBoard() << endl;
		piece->setCurrPosInBoard(piece->getInitialPosInBoard());
		piece->hasBeenCaptured = false;
		//cout << "Now " << piece->getName() << " initialPos =  " << piece->getInitialPosInBoard() << endl;
	}
}

Piece* Game::pixelPositionToPiece(const int& xPosInPixels, const int& yPosInPixels) {
	int posXInBoard, posYInBoard;
	posXInBoard = xPosInPixels / Piece::pieceSize.w;
	posYInBoard = yPosInPixels / Piece::pieceSize.w;
	Position posInBoard = Position(posXInBoard, posYInBoard);
	//cout << "posInBoard = " << posInBoard << endl;
	for (auto e : allPieces) {
		//cout << e->getName() << "is in " << e->getCurrPosInBoard() << endl;
		if (posInBoard == e->getCurrPosInBoard()) {
			return e;
		}
	}
	// if nothing is found
	return nullptr;
}

vector<Piece*> Game::getallPieces() {
	return allPieces;
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
		this->handleMouseButtonDown(event);
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
	case SDL_SCANCODE_R:
		reset();
		break;
	}// end switch key scancode
}

void Game::handleMouseButtonDown(SDL_Event& event) {

	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);

	this->currClickedPiece = pixelPositionToPiece(xPosInPixels, yPosInPixels);
}

void Game::handleMouseMotion(SDL_Event& event) {

	if (this->currClickedPiece == nullptr) {
		return;
	}

	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);
	Position pos = { xPosInPixels - Piece::pieceSize.w / 2, yPosInPixels - Piece::pieceSize.h / 2 };

	// IMPORTANT: we must not update position in board yet, thus, using 'false'
	this->currClickedPiece->setCurrPosInPixels(pos, false);

	render(this->currClickedPiece);
}

void Game::handleMouseButtonUp(SDL_Event& event) {

	if (this->currClickedPiece == nullptr) {
		return;
	}

	cout << "this->currClickedPiece = " << this->currClickedPiece->getName() << endl;

	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);

	Position posInPixels = { xPosInPixels, yPosInPixels };
	Position posInBoard  = { xPosInPixels / Piece::pieceSize.w, yPosInPixels / Piece::pieceSize.h };

	Piece* targetPiece = pixelPositionToPiece(xPosInPixels, yPosInPixels);

	if (targetPiece) {
		cout << "targetpiece = " << targetPiece->getName() << endl;
	}else{ cout << "targetpiece = nullptr" << endl; }
	

	// check legal moves
	if (!this->currClickedPiece->isLegalMove(posInBoard)) {
		// must render back to original position
		// and then return
		return;
	}

	// if nothing in the square, or if putting same piece back on it
	if (targetPiece == nullptr || !isDifferentPiece(this->currClickedPiece, targetPiece)) {
		// put the piece in the square where the mouse stopped
		this->currClickedPiece->setCurrPosInBoard(posInBoard);
	}
	else {
		// check capture or not
		if (isDifferentColor(this->currClickedPiece, targetPiece)) {
			// capture
			cout << "different color pieces" << endl;
			targetPiece->capturedPieceRoutine();
			this->currClickedPiece->setCurrPosInBoard(posInBoard);
		}
		else { // not a capture
			cout << "same color pieces" << endl;
			// will be treated later, just checking if position is identified
			this->currClickedPiece->setCurrPosInBoard(Position(0, 0));
		}
	}


	// check pieces of same color
	// check valid moves os pieces
	// check if not putting king in check

	this->currClickedPiece = nullptr;
	targetPiece = nullptr;
	delete targetPiece;

	// change turns;
	this->colorTurn = (this->colorTurn == ChessElementColor::WHITE ? ChessElementColor::BLACK : ChessElementColor::WHITE);
	cout << "Now it's " << this->colorTurn << "'s turn" << endl;
}

bool Game::isYourTurn() {
	if (this->currClickedPiece == nullptr) { return false; }
	return (this->currClickedPiece->getColor() == this->colorTurn);
}

bool Game::isDifferentColor(Piece* p1, Piece* p2) {
	return (p1->getColor() == p1->getColor());
}

bool Game::isDifferentPiece(Piece* p1, Piece* p2){
	return (p1 != p2);
}