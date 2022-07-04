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
	
	King* k = DBG_NEW King();
	k->setCurrPosInPixels(Position(50, 50));
	
	delete k;

	Game game;
	game.init();

	/* Board */
	//game.allPieces.push_back(DBG_NEW Board());

	//Board* b = DBG_NEW Board();
	//delete b;

	///* Pieces */
	//for (int i = 0; i < 8; i++) {
	//	game.allPieces.push_back(DBG_NEW Pawn(ChessElementColor::WHITE, "White Pawn" + to_string(i)));
	//	game.allPieces.push_back(DBG_NEW Pawn(ChessElementColor::BLACK, "Black Pawn" + to_string(i)));
	//}
	//for (int i = 0; i < 2; i++) {
	//	game.allPieces.push_back(DBG_NEW Bishop(ChessElementColor::WHITE, "White Bishop" + to_string(i)));
	//	game.allPieces.push_back(DBG_NEW Bishop(ChessElementColor::BLACK, "Black Bishop" + to_string(i)));

	//	game.allPieces.push_back(DBG_NEW Knight(ChessElementColor::WHITE, "White Knight" + to_string(i)));
	//	game.allPieces.push_back(DBG_NEW Knight(ChessElementColor::BLACK, "Black Knight" + to_string(i)));

	//	game.allPieces.push_back(DBG_NEW Rook(ChessElementColor::WHITE, "White Rook" + to_string(i)));
	//	game.allPieces.push_back(DBG_NEW Rook(ChessElementColor::BLACK, "Black Rook" + to_string(i)));
	//}

	//game.allPieces.push_back(DBG_NEW Queen(ChessElementColor::WHITE, "White Queen"));
	//game.allPieces.push_back(DBG_NEW Queen(ChessElementColor::BLACK, "White Queen"));

	//game.allPieces.push_back(DBG_NEW King(ChessElementColor::WHITE, "Black King"));
	//game.allPieces.push_back(DBG_NEW King(ChessElementColor::BLACK, "Black King"));

	//game.renderallPieces();

	//ChessElement el = game.getgame.allPieces().at(1);
	//cout << el.getName() << endl;
	//
	//Position pos = { 400, 400 };
	//vector<ChessElement*> vec_ce_pointer;
	//vec_ce_pointer.push_back(&el);
	//cout << vec_ce_pointer.at(0)->getName() << endl;
	//Piece* piece = static_cast<Piece*>(vec_ce_pointer[0]);
	//cout << piece->getName() << endl;
	//cout << "before = " << piece->getCurrPosInPixels().x <<","<< piece->getCurrPosInPixels().y << endl;
	//piece->setCurrPosInPixels(pos);
	//cout << "after = " << piece->getCurrPosInPixels().x << "," << piece->getCurrPosInPixels().y << endl;
	//cout << "before render" << endl;
	//game.render(*piece);
	//cout << "after render" << endl;
	//game.show();
	//cout << "after show" << endl;

	while (!game.closeGame) {
		SDL_Event event;

		// Events management
		while (SDL_PollEvent(&event)) {
			game.handleEvents(event);
		}// end while event

		
		
		//Piece* piece = static_cast<Piece*>(game.allPieces[1]);
		//
		////Position pos = { piece->getCurrPosInPixels().x, piece->getCurrPosInPixels().y};
		//Position pos = { 400, 400};
		//piece->setCurrPosInPixels(pos);
		////game.render(*piece);
		////game.show();
		//
		game.renderAllElements();

		// calculates to 60 fps
		SDL_Delay(1000 / GAME_FPS);

	}// end while(!closeGame)

	cout << "running memory leaks()" << endl;
	_CrtDumpMemoryLeaks();

	return 0;

}