#include <iostream>
#include "Utils.h"
#include "ChessElement.h"

using namespace std;

ChessElement::ChessElement(ChessElementColor color, string imgFilename,  SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, string name)
	: imgFilename(imgFilename), color(color), texture(texture), srcRect(srcRect), dstRect(dstRect), name(name) {

}

ChessElement::~ChessElement() {
	//SDL_DestroyTexture(texture);

	/*delete srcRect;
	delete dstRect;*/
}