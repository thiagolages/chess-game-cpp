#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include <string>

class Pawn : public Piece {

public:
	Pawn(ChessElementColor color = ChessElementColor::NONE, string name = "Pawn");
	~Pawn();

private:
	static int whitePawnCounter, blackPawnCounter; // to count number of created pawns and infere its position
	/*inline static string whitePawnFilename = IMG_PIECES_DIR+"wp.png";
	inline static string blackPawnFilename = IMG_PIECES_DIR+"bp.png";*/
	string whitePawnFilename = "images/pieces/wp.png";
	string blackPawnFilename = "images/pieces/bp.png";
};
#endif // !PAWN_H