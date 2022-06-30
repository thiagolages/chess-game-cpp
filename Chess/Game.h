#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include "AllChessPieces.h"
#include "Board.h"
#include <vector>

using namespace std;

extern const int maxNumPawns;
extern const int maxNumMiddlePieces;

class Game {

public:
	Game(bool closeGame=false, SDL_Renderer* rend=nullptr, SDL_Window* window=nullptr);
	~Game();
	void init();
	void gameSDL_init();
	void render(ChessElement ce);
	SDL_Renderer* rend;
	bool closeGame;

private:
	
	SDL_Window* window;
	SDL_Texture* windowTexture;
	
	//SDL_Rect* calcRenderPosition(ChessElement element);
	
	vector<ChessElement>	allElements;
	//vector<Pawn>	whitePawns	, blackPawns;
	//vector<Bishop>	whiteBishops, blackBishops;
	//vector<Knight>	whiteKnights, blackKnights;
	//vector<Rook>	whiteRooks	, blackRooks;
	//Queen			whiteQueen	, blackQueen;
	//King			whiteKing	, blackKing; 

};

#endif // !GAME_H