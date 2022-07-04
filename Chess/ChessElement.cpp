#include <iostream>
#include "Utils.h"
#include "ChessElement.h"

using namespace std;

ChessElement::ChessElement(ChessElementColor color, string imgFilename,  SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, string name)
	: imgFilename(imgFilename), color(color), texture(texture), srcRect(srcRect), 
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

ostream& operator<< (ostream& out, const ChessElementColor color) {

	switch (color) {
	case ChessElementColor::WHITE:
		out << "WHITE";
		break;
	case ChessElementColor::BLACK:
		out << "BLACK";
		break;
	case ChessElementColor::NONE:
		out << "NONE";
		break;
	default:
		break;
	}
	return out;
}