#include "Bishop.h"
#include <iostream>

int Bishop::whiteBishopCounter = 0; // initialize 
int Bishop::blackBishopCounter = 0; // initialize 
const string Bishop::whiteBishopFilename = IMG_PIECES_DIR + "wb.png";
const string Bishop::blackBishopFilename = IMG_PIECES_DIR + "bb.png";

using namespace std;

Bishop::~Bishop() {
}

Bishop::Bishop(PieceColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == PieceColor::WHITE ? whiteBishopFilename : blackBishopFilename);

	if (getColor() != PieceColor::WHITE && getColor() != PieceColor::BLACK) {
		cerr << "Wrong color passed to Bishop constructor !" << endl;
	}

	int counter = getColor() == PieceColor::WHITE ? whiteBishopCounter : blackBishopCounter;	// get correct Bishop counter to infere correct position
	int yRow	= getColor() == PieceColor::WHITE ? 7 : 0;									// spawn Bishops on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = counter == 0 ? 2 * CANVAS_WIDTH / 8 : 5 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
	Position boardPos = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(boardPos);

	cout << "setting " << name << " initial position to " << getInitialPosInBoard() << endl;

	// increment number of created bishops
	getColor() == PieceColor::WHITE ? Bishop::whiteBishopCounter++ : Bishop::blackBishopCounter++;
}


vector<Position> Bishop::calcMoves() {
	
	vector<Position> vec;

	for (int delta = 1; delta < horizontalSquares; delta++) {
		Position curr = getCurrPosInBoard();
		/* diagonals */
		if (isWithinBoardLimits(curr.x +  delta, curr.y +  delta)) vec.push_back(Position(curr.x +  delta, curr.y +  delta));
		if (isWithinBoardLimits(curr.x +  delta, curr.y + -delta)) vec.push_back(Position(curr.x +  delta, curr.y + -delta));
		if (isWithinBoardLimits(curr.x + -delta, curr.y +  delta)) vec.push_back(Position(curr.x + -delta, curr.y +  delta));
		if (isWithinBoardLimits(curr.x + -delta, curr.y + -delta)) vec.push_back(Position(curr.x + -delta, curr.y + -delta));
	}

	return vec;
}