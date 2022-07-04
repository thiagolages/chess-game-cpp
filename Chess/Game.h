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
	void show(); // actually show render on the screen
	void render(ChessElement* ce);
	void render(Position posInBoard);
	void renderAllElements();
	void handleEvents(SDL_Event &event);
	void handleKeyDown(SDL_Event &event);
	void handleMouseMotion(SDL_Event &event);
	void handleMouseButtonUp(SDL_Event& event);
	void handleMouseButtonDown(SDL_Event& event);
	Piece* pixelPositionToPiece(const int& x, const int& y);
	void drawCircle(Position center, int radius);
	void reset();
	bool isYourTurn();
	bool isDifferentColor(Piece* p1, Piece* p2);
	bool isDifferentPiece(Piece* p1, Piece* p2);
	SDL_Renderer* rend;
	bool closeGame;
	void changeTurns();
	void renderLegalMoves(Piece* piece);

private:
	Board* board;
	vector<Piece*>	allPieces;
	SDL_Window* window;
	SDL_Texture* windowTexture;
	Piece *currClickedPiece;
	ChessElementColor colorTurn;
	
	//SDL_Rect* calcRenderPosition(ChessElement element);	

};

#endif // !GAME_H