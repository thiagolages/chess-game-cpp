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
	inline static string whiteBishopFilename = IMG_PIECES_DIR+"wb.png";
	inline static string blackBishopFilename = IMG_PIECES_DIR+"bb.png";
};
#endif // !BISHOP_H