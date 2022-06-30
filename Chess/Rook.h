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
	inline static string whiteRookFilename = IMG_PIECES_DIR+"wr.png";
	inline static string blackRookFilename = IMG_PIECES_DIR+"br.png";
};
#endif // !ROOK_H