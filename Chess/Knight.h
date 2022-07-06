#ifndef KNIGHT_H
#define KNIGHT_H

#include "Utils.h"
#include "Piece.h"
#include <string>

class Knight : public Piece {

public:
	Knight(PieceColor color = PieceColor::NONE, string name="Knight");
	~Knight();

private:
	static int whiteKnightCounter, blackKnightCounter; // to count number of created bishops and infere its position
	static const string whiteKnightFilename;
	static const string blackKnightFilename;
	vector<Position> calcMoves();
};
#endif // !KNIGHT_H