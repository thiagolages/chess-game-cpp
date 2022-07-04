#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include <string>

class Rook : public Piece {

public:
	Rook(ChessElementColor color = ChessElementColor::NONE, string name="Rook");
	~Rook();

private:
	static int whiteRookCounter, blackRookCounter; // to count number of created bishops and infere its position
	static const string whiteRookFilename;
	static const string blackRookFilename;
};
#endif // !ROOK_H