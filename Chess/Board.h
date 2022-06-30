#ifndef BOARD_H
#define BOARD_H

#include "ChessElement.h"
#include <string>

using namespace std;

class Board : public ChessElement{
	public:
		Board(SDL_Texture* texture = nullptr, SDL_Rect* srcRect = nullptr, string name="board");
		~Board();
};
#endif // !BOARD_H