#ifndef CHESS_ELEMENT_H
#define CHESS_ELEMENT_H

#include <string>
#include <SDL.h>

using namespace std;


class ChessElement {

	public:
		ChessElement(string imgFilename = "", SDL_Texture * texture = nullptr, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, string name = "");
		~ChessElement();
		bool hasBeenCaptured;

	public:
		string getName();
		string imgFilename;
		SDL_Texture* texture;
		SDL_Rect* srcRect; // contains area which will be used from the source image for this ChessElement. Usually NULL (indicating the whole image will be used)
		SDL_Rect* dstRect; // contains area of the window (assigned to a renderer) which will be used. NULL indicates the whole window (tipically undesirable, unless filling whole background)
protected:
		string name;
};
#endif // !CHESS_ELEMENT_H