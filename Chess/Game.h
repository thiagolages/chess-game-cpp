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
	void renderAllElements();
	void handleEvents(SDL_Event &event);
	void handleKeyDown(SDL_Event &event);
	void handleMouseMotion(SDL_Event &event);
	void handleMouseButtonUp(SDL_Event& event);
	void handleMouseButtonDown(SDL_Event& event);
	Piece* pixelPositionToPiece(const int& x, const int& y);
	void reset();
	SDL_Renderer* rend;
	bool closeGame;
	vector<Piece*> getallPieces();
	

private:
	bool isResetting;
	Board* board;
	vector<Piece*>	allPieces;
	SDL_Window* window;
	SDL_Texture* windowTexture;
	bool isMouseClicked;
	Piece *currClickedPiece;
	
	//SDL_Rect* calcRenderPosition(ChessElement element);	

};

#endif // !GAME_H