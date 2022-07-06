#include "Rook.h"
#include <iostream>

int Rook::whiteRookCounter = 0; // initialize 
int Rook::blackRookCounter = 0; // initialize 

using namespace std;


const string Rook::whiteRookFilename = IMG_PIECES_DIR+"wr.png";
const string Rook::blackRookFilename = IMG_PIECES_DIR+"br.png";

Rook::~Rook() {
}

Rook::Rook(PieceColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == PieceColor::WHITE ? whiteRookFilename : blackRookFilename);

	if (getColor() != PieceColor::WHITE && getColor() != PieceColor::BLACK) {
		cerr << "Wrong color passed to Rook constructor !" << endl;
	}

	int counter = getColor() == PieceColor::WHITE ? whiteRookCounter : blackRookCounter;	// get correct Rook counter to infere correct position
	int yRow	= getColor() == PieceColor::WHITE ? 7 : 0;									// spawn Rooks on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = counter == 0 ? 0 : 7 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
	Position boardPos = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(boardPos);
	
	cout << "setting " << name << " initial position to " << getInitialPosInBoard() << endl;

	// increment number of created rooks
	getColor() == PieceColor::WHITE ? Rook::whiteRookCounter++ : Rook::blackRookCounter++;
}

vector<Position> Rook::calcMoves() {

	vector<Position> vec;

	for (int delta = 1; delta < horizontalSquares; delta++) {

		Position curr = getCurrPosInBoard();
		/* up/down */
		if (isWithinBoardLimits(curr.x, curr.y + delta)) vec.push_back(Position(curr.x, curr.y + delta));
		if (isWithinBoardLimits(curr.x, curr.y - delta)) vec.push_back(Position(curr.x, curr.y - delta));

		/* left/right */
		if (isWithinBoardLimits(curr.x + delta, curr.y)) vec.push_back(Position(curr.x + delta, curr.y));
		if (isWithinBoardLimits(curr.x - delta, curr.y)) vec.push_back(Position(curr.x - delta, curr.y));
	}

	return vec;
}