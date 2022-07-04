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
: closeGame(closeGame), rend(rend), window(window), 
  isMouseClicked(false), windowTexture(nullptr), currClickedPiece(nullptr) {
	
	///* Board */
	allElements.push_back(new Board());

	///* Pieces */
	for (int i = 0; i < 8; i++) {
		allElements.push_back(new Pawn (ChessElementColor::WHITE, "White Pawn"    + to_string(i)));
		allElements.push_back(new Pawn (ChessElementColor::BLACK, "Black Pawn"    + to_string(i)));
	}
	for (int i = 0; i < 2; i++) {
		allElements.push_back(new Bishop(ChessElementColor::WHITE, "White Bishop" + to_string(i)));
		allElements.push_back(new Bishop(ChessElementColor::BLACK, "Black Bishop" + to_string(i)));
		
		allElements.push_back(new Knight(ChessElementColor::WHITE, "White Knight" + to_string(i)));
		allElements.push_back(new Knight(ChessElementColor::BLACK, "Black Knight" + to_string(i)));
		
		allElements.push_back(new Rook  (ChessElementColor::WHITE, "White Rook"   + to_string(i)));
		allElements.push_back(new Rook  (ChessElementColor::BLACK, "Black Rook"   + to_string(i)));
	}

	allElements.push_back(new Queen(ChessElementColor::WHITE, "White Queen"));
	allElements.push_back(new Queen(ChessElementColor::BLACK, "Black Queen"));

	allElements.push_back(new King(ChessElementColor::WHITE, "White King"));
	allElements.push_back(new King(ChessElementColor::BLACK, "Black King"));
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

	for (auto &element : allElements) {
		
		/*vector<ChessElement*> vec_ce_pointer;
		vec_ce_pointer.push_back(&element);
		Piece* piece = (Piece*)vec_ce_pointer[0];
		render(*piece);*/
		//Piece* piece = static_cast<Piece*>(element);
		//render(*piece);
		render(element);
		
	}
	show();
}

void Game::show() {
	SDL_RenderPresent(rend);
}

void Game::render(ChessElement* ce) {

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

void Game::handleKeyDown(SDL_Event &event) {
	switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_ESCAPE:
			this->closeGame = true;
			break;
	}// end switch key scancode
}

void Game::handleMouseMotion(SDL_Event &event) {
	//cout << "[handleMouseMotion]event.type = " << event.type << endl;

	if (this->currClickedPiece == nullptr) {
		return;
	}

	int x, y;
	SDL_GetMouseState(&x, &y);
	Position pos = { x - Piece::pieceSize.w / 2, y - Piece::pieceSize.h / 2 };

	//cout << "MosePos = " << x << "," << y << endl;
	
	this->currClickedPiece->setCurrPosInPixels(pos);
	render(this->currClickedPiece);


	/*
	Piece* piece = static_cast<Piece*>(allElements[1]);
	piece->setCurrPosInPixels(pos);
	render(piece);
	piece = nullptr;
	delete piece;*/
}

void Game::handleEvents(SDL_Event &event) {
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

void Game::handleMouseButtonDown(SDL_Event& event) {

	this->isMouseClicked = true;
	int xPosInPixels, yPosInPixels;
	SDL_GetMouseState(&xPosInPixels, &yPosInPixels);
	this->currClickedPiece = pixelPositionToPiece(xPosInPixels, yPosInPixels);
	if (this->currClickedPiece == nullptr) {
		cerr << "Clicked piece is invalid !" << endl;
	}else {
		cout << "Clicked piece is = " << this->currClickedPiece->getName() << endl;
	}
}

Piece* Game::pixelPositionToPiece(const int &xPosInPixels, const int & yPosInPixels) {
	int posXInBoard, posYInBoard;
	posXInBoard = xPosInPixels / Piece::pieceSize.w;
	posYInBoard = yPosInPixels / Piece::pieceSize.w;
	Position posInBoard = Position(posXInBoard, posYInBoard);
	for (auto e : allElements) {
		//Piece* p = static_cast<Piece*> (e);
		if (posInBoard == static_cast<Piece*>(e)->getCurrPosInBoard()) {
			return static_cast<Piece*>(e);
		}
	}
	// if nothinf is found
	return nullptr;
}

void Game::handleMouseButtonUp(SDL_Event& event){
	int x, y;
	SDL_GetMouseState(&x, &y);

	this->isMouseClicked = false;
	this->currClickedPiece == nullptr;
	
}

vector<ChessElement*> Game::getAllElements() {
	return allElements;
}