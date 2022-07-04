#include "Utils.h"
#include "King.h"
#include <iostream>

using namespace std;

const string King::whiteKingFilename = IMG_PIECES_DIR + "wk.png";
const string King::blackKingFilename = IMG_PIECES_DIR + "bk.png";

King::~King() {
}

King::King(ChessElementColor color, string name)
	:Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == ChessElementColor::WHITE ? whiteKingFilename : blackKingFilename);

	int yRow = getColor() == ChessElementColor::WHITE ? 7 : 0;									// spawn Bishops on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = 4 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;
	setCurrPosInPixels(pos);
	Position posInBoard = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(posInBoard);
	cout << "setting " << name << "initial position to " << getInitialPosInBoard() << endl;
}

vector<Position> King::calcMoves() {

	vector<Position> vec;

	int delta = 1;
	/* diagonals */
	vec.push_back(Position(delta, delta));
	vec.push_back(Position(delta, -delta));
	vec.push_back(Position(-delta, delta));
	vec.push_back(Position(-delta, -delta));

	/* up/down */
	vec.push_back(Position(0, delta));
	vec.push_back(Position(0, -delta));

	/* left/right */
	vec.push_back(Position(delta, 0));
	vec.push_back(Position(-delta, 0));


	return vec;
}