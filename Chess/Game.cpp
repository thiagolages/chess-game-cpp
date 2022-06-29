#include <iostream>
#include <SDL.h>

#include "Utils.h"
#include "AllChessPieces.h"
#include "Game.h"

using namespace std;

Game::Game(bool closeGame, SDL_Renderer *rend, SDL_Window *window) 
: closeGame(closeGame), rend(rend), window(window) {

}

Game::~Game() {
	// destroy renderer
	SDL_DestroyRenderer(rend);
	// destroy window
	SDL_DestroyWindow(window);
	// closeGame SDL
	SDL_Quit();
}

void Game::init() {
	
	gameSDL_init();
	renderBoard();
	renderPieces();

}

void Game::gameSDL_init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
	}

	window = SDL_CreateWindow("Chess - by Thiago Lages (@thiagolages)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CANVAS_WIDTH, CANVAS_HEIGHT, 0);

	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		SDL_Quit();
	}
	// triggers the program that controls your graphics hardware and sets flags
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images
	rend = SDL_CreateRenderer(window, -1, render_flags);

}

void  Game::renderBoard() {

	string board_filename = IMG_BOARDS_DIR + "board.jpg";
	ChessPiece board = ChessPiece(PieceColor::NONE, board_filename, rend);
	board.render();
}

void Game::renderPieces() {
	const int maxPawns = 8;
	Pawn *whitePawns[maxPawns], *blackPawns[maxPawns];
	for (int i = 0; i < maxPawns; i++) {
		whitePawns[i] = new Pawn(PieceColor::WHITE, rend);
		blackPawns[i] = new Pawn(PieceColor::BLACK, rend);

		whitePawns[i]->render();
		blackPawns[i]->render();
	}

	const int maxMiddlePieces = 2;
	Rook* whiteRooks[maxMiddlePieces], * blackRooks[maxMiddlePieces];
	for (int i = 0; i < maxMiddlePieces; i++) {
		whiteRooks[i] = new Rook(PieceColor::WHITE, rend);
		blackRooks[i] = new Rook(PieceColor::BLACK, rend);

		whiteRooks[i]->render();
		blackRooks[i]->render();
	}

	Knight* whiteKnights[maxMiddlePieces], * blackKnights[maxMiddlePieces];
	for (int i = 0; i < maxMiddlePieces; i++) {
		whiteKnights[i] = new Knight(PieceColor::WHITE, rend);
		blackKnights[i] = new Knight(PieceColor::BLACK, rend);

		whiteKnights[i]->render();
		blackKnights[i]->render();
	}

	Bishop* whiteBishops[maxMiddlePieces], * blackBishops[maxMiddlePieces];
	for (int i = 0; i < maxMiddlePieces; i++) {
		whiteBishops[i] = new Bishop(PieceColor::WHITE, rend);
		blackBishops[i] = new Bishop(PieceColor::BLACK, rend);

		whiteBishops[i]->render();
		blackBishops[i]->render();
	}

	Queen *whiteQueen, *blackQueen;
	
	whiteQueen = new Queen(PieceColor::WHITE, rend);
	blackQueen = new Queen(PieceColor::BLACK, rend);

	whiteQueen->render();
	blackQueen->render();

	King* whiteKing, * blackKing;

	whiteKing = new King(PieceColor::WHITE, rend);
	blackKing = new King(PieceColor::BLACK, rend);

	whiteKing->render();
	blackKing->render();
	
}

void Game::render() {
	// clears the screen
	//SDL_RenderClear(rend);
	SDL_RenderPresent(rend);
	SDL_RenderCopy(rend, windowTexture, nullptr, nullptr);
}