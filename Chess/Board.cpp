#include "Utils.h"
#include "Board.h"

Board::Board(SDL_Texture* texture, SDL_Rect* srcRect, string name)
: ChessElement(IMG_BOARDS_DIR+"board.png", texture, srcRect, nullptr, name) {

}

Board::~Board() {
	//SDL_DestroyTexture(texture);
	SDL_DestroyTexture(this->texture);
	delete this->srcRect;
	delete this->dstRect;
}