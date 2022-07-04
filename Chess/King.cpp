#include "Utils.h"
#include "King.h"
#include <iostream>

using namespace std;

const string King::whiteKingFilename = IMG_PIECES_DIR + "wk.png";
const string King::blackKingFilename = IMG_PIECES_DIR + "bk.png";

King::~King() {
	cout << "destructor() King" << name << endl;
}

King::King(ChessElementColor color, string name)
	:Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == ChessElementColor::WHITE ? whiteKingFilename : blackKingFilename);

	int yRow = getColor() == ChessElementColor::WHITE ? 7 : 0;									// spawn Bishops on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = 4 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;
	setCurrPosInPixels(pos);
}