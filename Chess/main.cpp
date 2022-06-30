#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>

#include <filesystem>
#include "Game.h"
#include "Piece.h"
#include "Utils.h"

using namespace std;


int main(int argc, char* argv[]){

	Game game;
	game.init();

	SDL_RenderPresent(game.rend);

	while (!game.closeGame) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			switch (event.type) {

			case SDL_QUIT:
				// handling of closeGame button
				game.closeGame = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					game.closeGame = true;
					break;
				}// end switch key scancode
			}// end switch event
		}// end while event

		//SDL_RenderClear(game.rend);
		//SDL_RenderPresent(game.rend);
		//SDL_RenderCopy(game.rend texture, nullptr, nullptr);

		// calculates to 60 fps
		SDL_Delay(1000 / GAME_FPS);

	}// end while(!closeGame)


	////_CrtDumpMemoryLeaks();
	return 0;

}