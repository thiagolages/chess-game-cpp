#include <iostream>
#include <SDL.h>

#include "Utils.h"
#include "AllChessPieces.h"
#include "Game.h"

using namespace std;

const int maxNumPawns		= 8;
const int maxNumMiddlePieces= 2;

Game::Game(bool closeGame, SDL_Renderer *rend, SDL_Window *window) 
: closeGame(closeGame), rend(rend), window(window) {
	
	/* Board */
	allElements.push_back(Board());
	
	/* Pieces */
	for (int i = 0; i < 8; i++) {
		allElements.push_back(Pawn(ChessElementColor::WHITE, "White Pawn" + to_string(i)));
		allElements.push_back(Pawn(ChessElementColor::BLACK, "Black Pawn" + to_string(i)));
	}
	for (int i = 0; i < 2; i++) {
		allElements.push_back(Bishop(ChessElementColor::WHITE, "White Bishop" + to_string(i)));
		allElements.push_back(Bishop(ChessElementColor::BLACK, "Black Bishop" + to_string(i)));
		
		allElements.push_back(Knight(ChessElementColor::WHITE, "White Knight" + to_string(i)));
		allElements.push_back(Knight(ChessElementColor::BLACK, "Black Knight" + to_string(i)));
		
		allElements.push_back(Rook(ChessElementColor::WHITE, "White Rook" + to_string(i)));
		allElements.push_back(Rook(ChessElementColor::BLACK, "Black Rook" + to_string(i)));
	}

	allElements.push_back(Queen(ChessElementColor::WHITE, "White Queen"));
	allElements.push_back(Queen(ChessElementColor::BLACK, "White Queen"));

	allElements.push_back(King(ChessElementColor::WHITE, "Black King"));
	allElements.push_back(King(ChessElementColor::BLACK, "Black King"));
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
	for (auto &element : allElements) {
		render(element);
	}
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

void Game::render(ChessElement ce) {

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
	ce.texture = IMG_LoadTexture(rend, ce.imgFilename.c_str());
	
	// enhance the quality of the texture
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	if (ce.texture == NULL) {
		std::cout << "couldnt create texture from surface " << std::endl;
		cout << IMG_GetError() << endl;
	}

	SDL_RenderCopy(rend, ce.texture, ce.srcRect, ce.dstRect);

}