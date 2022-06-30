#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include <string>

class Queen : public Piece {

public:
	Queen(ChessElementColor color = ChessElementColor::NONE, string name="Queen");
	~Queen();

private:
	inline static string whiteQueenFilename = IMG_PIECES_DIR+"wq.png";
	inline static string blackQueenFilename = IMG_PIECES_DIR+"bq.png";
};
#endif // !QUEEN_H