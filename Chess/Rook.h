#ifndef ROOK_H
#define ROOK_H

#include "Utils.h"
#include "Piece.h"
#include <string>

class Rook : public Piece {

public:
	Rook(PieceColor color = PieceColor::NONE, string name="Rook");
	~Rook();

private:
	static int whiteRookCounter, blackRookCounter; // to count number of created bishops and infere its position
	static const string whiteRookFilename;
	static const string blackRookFilename;
	vector<Position> calcMoves();
};
#endif // !ROOK_H