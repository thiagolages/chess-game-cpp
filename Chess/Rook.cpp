#include "Utils.h"
#include "Rook.h"
#include <iostream>

int Rook::whiteRookCounter = 0; // initialize 
int Rook::blackRookCounter = 0; // initialize 

using namespace std;

const string Rook::whiteRookFilename = IMG_PIECES_DIR+"wr.png";
const string Rook::blackRookFilename = IMG_PIECES_DIR+"br.png";

Rook::~Rook() {
}

Rook::Rook(ChessElementColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == ChessElementColor::WHITE ? whiteRookFilename : blackRookFilename);

	if (getColor() != ChessElementColor::WHITE && getColor() != ChessElementColor::BLACK) {
		cerr << "Wrong color passed to Rook constructor !" << endl;
	}

	int counter = getColor() == ChessElementColor::WHITE ? whiteRookCounter : blackRookCounter;	// get correct Rook counter to infere correct position
	int yRow	= getColor() == ChessElementColor::WHITE ? 7 : 0;									// spawn Rooks on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = counter == 0 ? 0 : 7 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
	Position posInBoard = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(posInBoard);
	
	cout << "setting " << name << "initial position to " << getInitialPosInBoard() << endl;

	// increment number of created rooks
	getColor() == ChessElementColor::WHITE ? Rook::whiteRookCounter++ : Rook::blackRookCounter++;
}

vector<Position> Rook::calcMoves() {

	vector<Position> vec;

	for (int delta = 1; delta < horizontalSquares; delta++) {

		/* up/down */
		vec.push_back(Position(0, delta));
		vec.push_back(Position(0, -delta));

		/* left/right */
		vec.push_back(Position(delta, 0));
		vec.push_back(Position(-delta, 0));
	}

	return vec;
}