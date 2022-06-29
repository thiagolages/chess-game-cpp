#pragma once
#include <SDL.h>
#include <string>

using namespace std;	

class ChessPiece {
public:
	ChessPiece(SDL_Renderer* rend, string filename, SDL_Rect* srcRect=NULL, SDL_Rect* dstRect=NULL);
	~ChessPiece();
	void render();
private:
	string filename;
	SDL_Renderer*  rend;
	SDL_Texture* texture;
	SDL_Surface* image;
	SDL_Rect *srcRect, *dstRect;
};
