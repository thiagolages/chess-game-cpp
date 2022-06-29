#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "ChessPiece.h"
#include "Constants.h"

ChessPiece::ChessPiece(SDL_Renderer* rend, string filename, SDL_Rect* srcRect, SDL_Rect* dstRect) : rend(rend),filename(filename), srcRect(srcRect), dstRect(dstRect) {
	
}

ChessPiece::~ChessPiece() {
	SDL_DestroyTexture(texture);
}

void ChessPiece::render() {

	// SDL_Renderer * rend, string filename, SDL_Rect * srcRect, SDL_Rect * dstRect

		image = IMG_Load(filename.c_str());

		if (image == NULL) {
			std::cout << "couldnt load " << filename << std::endl;
			cout << IMG_GetError() << endl;
		}

		texture = SDL_CreateTextureFromSurface(rend, image);

		SDL_RenderCopy(rend, texture, srcRect, dstRect);
		SDL_RenderPresent(rend);

	
}