#include "Utils.h"
#include "Bishop.h"
#include <iostream>

int Bishop::whiteBishopCounter = 0; // initialize 
int Bishop::blackBishopCounter = 0; // initialize 
const string Bishop::whiteBishopFilename = IMG_PIECES_DIR + "wb.png";
const string Bishop::blackBishopFilename = IMG_PIECES_DIR + "bb.png";

using namespace std;

Bishop::~Bishop() {
}

Bishop::Bishop(ChessElementColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == ChessElementColor::WHITE ? whiteBishopFilename : blackBishopFilename);

	if (getColor() != ChessElementColor::WHITE && getColor() != ChessElementColor::BLACK) {
		cerr << "Wrong color passed to Bishop constructor !" << endl;
	}

	int counter = getColor() == ChessElementColor::WHITE ? whiteBishopCounter : blackBishopCounter;	// get correct Bishop counter to infere correct position
	int yRow	= getColor() == ChessElementColor::WHITE ? 7 : 0;									// spawn Bishops on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = counter == 0 ? 2 * CANVAS_WIDTH / 8 : 5 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
	Position posInBoard = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(posInBoard);

	cout << "setting " << name << "initial position to " << getInitialPosInBoard() << endl;

	// increment number of created bishops
	getColor() == ChessElementColor::WHITE ? Bishop::whiteBishopCounter++ : Bishop::blackBishopCounter++;
}


