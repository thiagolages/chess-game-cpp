#include "King.h"
#include <iostream>

using namespace std;


const string King::whiteKingFilename = IMG_PIECES_DIR + "wk.png";
const string King::blackKingFilename = IMG_PIECES_DIR + "bk.png";

King::~King() {
}

King::King(PieceColor color, string name)
	:Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == PieceColor::WHITE ? whiteKingFilename : blackKingFilename);

	int yRow = getColor() == PieceColor::WHITE ? 7 : 0;									// spawn Bishops on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = 4 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;
	setCurrPosInPixels(pos);
	Position boardPos = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(boardPos);
	cout << "setting " << name << " initial position to " << getInitialPosInBoard() << endl;
}

vector<Position> King::calcMoves() {

	vector<Position> vec;

	int delta = 1;
	Position curr = getCurrPosInBoard();
	/* diagonals */
	if (isWithinBoardLimits(curr.x + delta, curr.y + delta)) vec.push_back(Position(curr.x + delta, curr.y + delta));
	if (isWithinBoardLimits(curr.x + delta, curr.y - delta)) vec.push_back(Position(curr.x + delta, curr.y - delta));
	if (isWithinBoardLimits(curr.x - delta, curr.y + delta)) vec.push_back(Position(curr.x - delta, curr.y + delta));
	if (isWithinBoardLimits(curr.x - delta, curr.y - delta)) vec.push_back(Position(curr.x - delta, curr.y - delta));

	/* up/down */
	if (isWithinBoardLimits(curr.x, curr.y + delta)) vec.push_back(Position(curr.x, curr.y + delta));
	if (isWithinBoardLimits(curr.x, curr.y - delta)) vec.push_back(Position(curr.x, curr.y - delta));

	/* left/right */
	if (isWithinBoardLimits(curr.x + delta, curr.y)) vec.push_back(Position(curr.x + delta, curr.y));
	if (isWithinBoardLimits(curr.x - delta, curr.y)) vec.push_back(Position(curr.x - delta, curr.y));


	return vec;
}