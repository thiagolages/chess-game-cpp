#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <string>

class Queen : public Piece {

public:
	Queen(ChessElementColor color = ChessElementColor::NONE, string name="Queen");
	~Queen();

private:
	static const string whiteQueenFilename;
	static const string blackQueenFilename;
	virtual vector<Position> calcMoves();
};
#endif // !QUEEN_H