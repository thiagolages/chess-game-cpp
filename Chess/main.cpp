#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <stdlib.h>
#include <crtdbg.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>

#include <filesystem>
#include "Game.h"
#include "Utils.h"
#include"King.h"
using namespace std;



int main(int argc, char* argv[]){
	
	//_CrtSetBreakAlloc(200);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game game;
	game.init();

	while (!game.closeGame) {
		
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			game.handleEvents(event);
		}

		game.renderAll();
		//SDL_Delay(1000 / GAME_FPS);
	}

	cout << "running memory leaks()" << endl;
	_CrtDumpMemoryLeaks();

	return 0;

}