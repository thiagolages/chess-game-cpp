#ifndef BISHOP_H
#define BISHOP_H

#include "Utils.h"
#include "Piece.h"
#include <string>

class Bishop : public Piece {

public:
	Bishop(PieceColor color = PieceColor::NONE, string name="Bishop");
	~Bishop();

private:
	static int whiteBishopCounter, blackBishopCounter; // to count number of created bishops and infere its position
	static const string whiteBishopFilename;
	static const string blackBishopFilename;
	vector<Position> calcMoves();
};
#endif // !BISHOP_H