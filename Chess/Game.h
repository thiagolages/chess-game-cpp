#ifndef GAME_H
#define GAME_H

#include <SDL.h>

class Game {

public:
	Game(bool closeGame=false, SDL_Renderer* rend=nullptr, SDL_Window* window=nullptr);
	~Game();
	void init();
	void gameSDL_init();
	void renderBoard();
	void renderPieces();
	void render();
	SDL_Renderer* rend;
	bool closeGame;

private:
	SDL_Window *window;
	SDL_Texture*windowTexture;

};

#endif // !GAME_H