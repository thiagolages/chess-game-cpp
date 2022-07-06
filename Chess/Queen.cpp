#include "Queen.h"
#include <iostream>

using namespace std;


const string Queen::whiteQueenFilename = IMG_PIECES_DIR+"wq.png";
const string Queen::blackQueenFilename = IMG_PIECES_DIR+"bq.png";

Queen::~Queen() {
}

Queen::Queen(PieceColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == PieceColor::WHITE ? whiteQueenFilename : blackQueenFilename);

	if (getColor() != PieceColor::WHITE && getColor() != PieceColor::BLACK) {
		cerr << "Wrong color passed to Queen constructor !" << endl;
	}

	int yRow = getColor() == PieceColor::WHITE ? 7 : 0;									// spawn Queens on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = 3 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
	Position boardPos = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(boardPos);
	cout << "setting " << name << " initial position to " << getInitialPosInBoard() << endl;
}

vector<Position> Queen::calcMoves() {

	vector<Position> vec;

	for (int delta = 1; delta < horizontalSquares; delta++) {
		Position curr = getCurrPosInBoard();
		/* diagonals */
		if (isWithinBoardLimits(curr.x +  delta, curr.y +  delta)) vec.push_back(Position(curr.x +  delta, curr.y +  delta));
		if (isWithinBoardLimits(curr.x +  delta, curr.y -  delta)) vec.push_back(Position(curr.x +  delta, curr.y -  delta));
		if (isWithinBoardLimits(curr.x -  delta, curr.y +  delta)) vec.push_back(Position(curr.x -  delta, curr.y +  delta));
		if (isWithinBoardLimits(curr.x -  delta, curr.y -  delta)) vec.push_back(Position(curr.x -  delta, curr.y -  delta));
		
		/* up/down */
		if (isWithinBoardLimits(curr.x, curr.y +  delta)) vec.push_back(Position(curr.x, curr.y +  delta));
		if (isWithinBoardLimits(curr.x, curr.y -  delta)) vec.push_back(Position(curr.x, curr.y -  delta));

		/* left/right */
		if (isWithinBoardLimits(curr.x + delta, curr.y)) vec.push_back(Position(curr.x + delta, curr.y));
		if (isWithinBoardLimits(curr.x - delta, curr.y)) vec.push_back(Position(curr.x - delta, curr.y));
	}

	return vec;
}