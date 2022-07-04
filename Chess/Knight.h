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
	static const string whiteKnightFilename;
	static const string blackKnightFilename;
};
#endif // !KNIGHT_H