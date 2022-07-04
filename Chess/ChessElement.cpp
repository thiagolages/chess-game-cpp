#include <iostream>
#include "Utils.h"
#include "ChessElement.h"

using namespace std;

ChessElement::ChessElement(ChessElementColor color, string imgFilename,  SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, string name)
	: imgFilename(imgFilename), color(color), texture(texture), srcRect(srcRect), dstRect(dstRect), name(name) {
	cout << "constructor() " << name << endl;
}

ChessElement::~ChessElement() {
		
	cout << "destructor() ChessElement" << name << endl;
	SDL_DestroyTexture(this->texture);
	
	delete this->srcRect;
	delete this->dstRect;
}

string ChessElement::getName() {
	return name;
}