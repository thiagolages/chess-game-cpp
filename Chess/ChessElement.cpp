#include <iostream>
#include "Utils.h"
#include "ChessElement.h"

using namespace std;


ChessElement::ChessElement(string imgFilename,  SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, string name)
	: imgFilename(imgFilename), texture(texture), srcRect(srcRect), 
	dstRect(dstRect), name(name), hasBeenCaptured(false) {
}

ChessElement::~ChessElement() {
		
	SDL_DestroyTexture(this->texture);
	
	delete this->srcRect;
	delete this->dstRect;
}

string ChessElement::getName() {
	return name;
}