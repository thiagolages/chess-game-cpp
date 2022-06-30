#include "Utils.h"
#include "King.h"
#include <iostream>

using namespace std;

King::~King() {
}

King::King(ChessElementColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == ChessElementColor::WHITE ? whiteKingFilename : blackKingFilename);

	if (getColor() != ChessElementColor::WHITE && getColor() != ChessElementColor::BLACK) {
		cerr << "Wrong color passed to King constructor !" << endl;
	}

	int yRow	= getColor() == ChessElementColor::WHITE ? 7 : 0;									// spawn Kings on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = 4 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
}