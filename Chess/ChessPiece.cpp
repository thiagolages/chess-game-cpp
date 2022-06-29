#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "ChessPiece.h"
#include "Utils.h"


ChessPiece::ChessPiece() : rend(nullptr), srcRect(nullptr), dstRect(nullptr),
texture(nullptr), image_surface(nullptr), imgFilename(""), color(PieceColor::NONE)
{	
	cout << "ChessPiece() default constructor" << endl;
}

ChessPiece::ChessPiece(PieceColor color, string imgFilename, SDL_Renderer* rend, SDL_Rect* srcRect, SDL_Rect* dstRect) : 
	color(color), imgFilename(imgFilename), rend(rend), srcRect(srcRect), dstRect(dstRect),
	image_surface(nullptr), texture(nullptr) 
{
	cout << "ChessPiece(...) constructor" << endl;
}

ChessPiece::~ChessPiece() {
	//SDL_DestroyRenderer(rend);
	//SDL_DestroyTexture(texture);
}

void ChessPiece::render() {
	
	cout << "imgFileName inside ChessPiece render() = " << imgFilename << endl;

	cout << "rend inside ChessPiece::render() == nullptr? " << (rend == nullptr ? "yes" : "no") << endl;

	image_surface = IMG_Load(imgFilename.c_str());

	if (image_surface == NULL) {
		std::cout << "couldnt load " << imgFilename << std::endl;
		cout << IMG_GetError() << endl;
	}
	// enhance the quality of the texture
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	texture = SDL_CreateTextureFromSurface(rend, image_surface);

	if (texture == NULL) {
		std::cout << "couldnt create texture from surface " << std::endl;
		cout << IMG_GetError() << endl;
	}

	cout << "inside ChessPiece render()" << endl;
	cout << "srcRect = " << srcRect << ", dstRect = " << dstRect << endl;
	//SDL_RenderClear(rend);
	SDL_RenderCopy(rend, texture, srcRect, dstRect);
	// not showing here yet, just including in the final texture.
	// final render will show all pieces on the screen
	//SDL_RenderPresent(rend);
}