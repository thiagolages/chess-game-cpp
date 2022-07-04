#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include <string>

class Bishop : public Piece {

public:
	Bishop(ChessElementColor color = ChessElementColor::NONE, string name="Bishop");
	~Bishop();

private:
	static int whiteBishopCounter, blackBishopCounter; // to count number of created bishops and infere its position
	static const string whiteBishopFilename;
	static const string blackBishopFilename;
	virtual vector<Position> calcMoves();
};
#endif // !BISHOP_H