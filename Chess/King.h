#ifndef KING_H
#define KING_H

#include "Piece.h"
#include <string>

class King : public Piece {

public:
	King(ChessElementColor color = ChessElementColor::NONE, string name="King");
	~King();

private:
	inline static string whiteKingFilename = IMG_PIECES_DIR+"wk.png";
	inline static string blackKingFilename = IMG_PIECES_DIR+"bk.png";
};
#endif // !KING_H