#ifndef KING_H
#define KING_H

#include "Utils.h"
#include "Piece.h"
#include <string>

class King : public Piece {

public:
	King(PieceColor color = PieceColor::NONE, string name="King");
	~King();

private:
	static const string whiteKingFilename;
	static const string blackKingFilename;
	vector<Position> calcMoves();
};
#endif // !KING_H