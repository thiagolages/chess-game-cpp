#ifndef QUEEN_H
#define QUEEN_H

#include "Utils.h"
#include "Piece.h"
#include <string>

class Queen : public Piece {

public:
	Queen(PieceColor color = PieceColor::NONE, string name="Queen");
	~Queen();

private:
	static const string whiteQueenFilename;
	static const string blackQueenFilename;
	vector<Position> calcMoves();
};
#endif // !QUEEN_H