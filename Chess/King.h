#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <string>

class King : public Piece {

public:
	King(ChessElementColor color = ChessElementColor::NONE, string name="King");
	~King();

private:
	static const string whiteKingFilename;
	static const string blackKingFilename;
};
#endif // !KING_H