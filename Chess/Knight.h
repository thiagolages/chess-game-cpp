#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include <string>

class Knight : public Piece {

public:
	Knight(ChessElementColor color = ChessElementColor::NONE, string name="Knight");
	~Knight();

private:
	static int whiteKnightCounter, blackKnightCounter; // to count number of created bishops and infere its position
	inline static string whiteKnightFilename = IMG_PIECES_DIR+"wn.png";
	inline static string blackKnightFilename = IMG_PIECES_DIR+"bn.png";
};
#endif // !KNIGHT_H