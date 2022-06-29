#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <iostream>

#include <filesystem>
#include "Game.h"
#include "ChessPiece.h"
#include "Utils.h"


using namespace std;

void renderBackground(SDL_Renderer*);

int main(int argc, char* argv[]){


	Game game;

	game.init();

	cout << IMG_PIECES_DIR << endl;
	cout << IMG_BOARDS_DIR << endl;
	//renderBackground(game.rend);


	//renderImage(game.rend board_filename);

	/*ChessPiece *whitePawns[8], *blackPawns[8];
	ChessPiece *whiteKnights[2], *blackKnights[2];
	ChessPiece *whiteBishops[2], *blackBishops[2];
	ChessPiece *whiteRooks  [2], *blackRooks  [2];
	ChessPiece *whiteQueen, *blackQueen;
	ChessPiece *whiteKing , *blackKing;

	for (int i = 0; i < 8; i++) {
		whitePawns[i] = new ChessPiece(PieceType::PAWN, PieceColor::WHITE, "images/pieces/wp.png", game.rend, NULL,
			new SDL_Rect{
			i * CANVAS_WIDTH / 8,
			6 * CANVAS_HEIGHT / 8,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT / 8 });
		
		blackPawns[i] = new ChessPiece(PieceType::PAWN, PieceColor::BLACK, "images/pieces/bp.png", game.rend, NULL,
			new SDL_Rect{ 
			i*CANVAS_WIDTH / 8,
			CANVAS_HEIGHT  / 8,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT  / 8 });
		
		whitePawns[i]->render();
		blackPawns[i]->render();		
	}

	for (int i = 0; i < 2; i++) {
		whiteRooks[i] = new ChessPiece(PieceType::ROOK, PieceColor::WHITE, "images/pieces/wr.png", game.rend, NULL,
			new SDL_Rect{
			i*7 * CANVAS_WIDTH / 8,
			7 * CANVAS_HEIGHT / 8,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT / 8 });
		
		blackRooks[i] = new ChessPiece(PieceType::ROOK, PieceColor::BLACK, "images/pieces/br.png", game.rend, NULL,
			new SDL_Rect{
			i * 7 * CANVAS_WIDTH / 8,
			0,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT / 8 });

		whiteKnights[i] = new ChessPiece(PieceType::KNIGHT, PieceColor::WHITE, "images/pieces/wn.png", game.rend, NULL,
			new SDL_Rect{
			((i*5)+1) * CANVAS_WIDTH / 8,
			7 * CANVAS_HEIGHT / 8,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT / 8 });
		
		blackKnights[i] = new ChessPiece(PieceType::KNIGHT, PieceColor::BLACK, "images/pieces/bn.png", game.rend, NULL,
			new SDL_Rect{
			((i * 5) + 1) * CANVAS_WIDTH / 8,
			0,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT / 8 });

		whiteBishops[i] = new ChessPiece(PieceType::BISHOP, PieceColor::WHITE, "images/pieces/wb.png", game.rend, NULL,
			new SDL_Rect{
			((i * 3) + 2) * CANVAS_WIDTH / 8,
			7 * CANVAS_HEIGHT / 8,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT / 8 });

		blackBishops[i] = new ChessPiece(PieceType::BISHOP, PieceColor::BLACK, "images/pieces/bb.png", game.rend, NULL,
			new SDL_Rect{
			((i * 3) + 2) * CANVAS_WIDTH / 8,
			0,
			CANVAS_WIDTH / 8,
			CANVAS_HEIGHT / 8 });

		whiteRooks[i]->render();
		blackRooks[i]->render();
		whiteKnights[i]->render();
		blackKnights[i]->render();
		whiteBishops[i]->render();
		blackBishops[i]->render();
	}


	whiteQueen = new ChessPiece(PieceType::QUEEN, PieceColor::WHITE, "images/pieces/wq.png", game.rend, NULL,
		new SDL_Rect{
		3 * CANVAS_WIDTH / 8,
		7 * CANVAS_HEIGHT / 8,
		CANVAS_WIDTH / 8,
		CANVAS_HEIGHT / 8 });

	blackQueen = new ChessPiece(PieceType::QUEEN, PieceColor::BLACK, "images/pieces/bq.png", game.rend, NULL,
		new SDL_Rect{
		3 * CANVAS_WIDTH / 8,
		0,
		CANVAS_WIDTH / 8,
		CANVAS_HEIGHT / 8 });

	whiteKing = new ChessPiece(PieceType::KING, PieceColor::WHITE, "images/pieces/wk.png", game.rend, NULL,
		new SDL_Rect{
		4 * CANVAS_WIDTH / 8,
		7 * CANVAS_HEIGHT / 8,
		CANVAS_WIDTH / 8,
		CANVAS_HEIGHT / 8 });

	blackKing = new ChessPiece(PieceType::KING, PieceColor::BLACK, "images/pieces/bk.png", game.rend, NULL,
		new SDL_Rect{
		4 * CANVAS_WIDTH / 8,
		0,
		CANVAS_WIDTH / 8,
		CANVAS_HEIGHT / 8 });

	whiteQueen->render();
	blackQueen->render();
	whiteKing->render();
	blackKing->render();*/

	//SDL_RenderClear(game.rend);
	SDL_RenderPresent(game.rend);

	//game.render();

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


	// destroy texture
	//SDL_DestroyTexture(tex);

	

	

	//for (int i = 0;i < 8;i++) {
	//	delete whitePawns[i];
	//	delete blackPawns[i];
	//}
	//for (int i = 0;i < 2;i++) {
	//	delete whiteKnights[i];
	//	delete blackKnights[i];
	//	delete whiteBishops[i];
	//	delete blackBishops[i];
	//	delete whiteRooks[i];
	//	delete blackRooks[i];
	//}
	//delete whiteQueen;
	//delete blackQueen;
	//delete whiteKing;
	//delete blackKing;
	//
	return 0;

}

void renderBackground(SDL_Renderer* rend)
{
	bool white = true;
	SDL_SetRenderDrawColor(rend , 255, 255, 255, 255);

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (white){
				SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
			}else{
				SDL_SetRenderDrawColor(rend, 155, 103, 60, 255);
			}
			white = !white;
			SDL_Rect rectangle ={ i * CANVAS_WIDTH / 8,
								  j * CANVAS_HEIGHT / 8,
								  CANVAS_WIDTH / 8,
								  CANVAS_HEIGHT / 8 };
			SDL_RenderFillRect(rend, &rectangle);
		}
		white = !white;
	}
}
