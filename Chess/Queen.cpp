#include "Utils.h"
#include "Queen.h"
#include <iostream>

using namespace std;

const string Queen::whiteQueenFilename = IMG_PIECES_DIR+"wq.png";
const string Queen::blackQueenFilename = IMG_PIECES_DIR+"bq.png";

Queen::~Queen() {
}

Queen::Queen(ChessElementColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == ChessElementColor::WHITE ? whiteQueenFilename : blackQueenFilename);

	if (getColor() != ChessElementColor::WHITE && getColor() != ChessElementColor::BLACK) {
		cerr << "Wrong color passed to Queen constructor !" << endl;
	}

	int yRow = getColor() == ChessElementColor::WHITE ? 7 : 0;									// spawn Queens on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = 3 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
}