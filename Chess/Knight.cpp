#include "Knight.h"
#include <iostream>

int Knight::whiteKnightCounter = 0; // initialize 
int Knight::blackKnightCounter = 0; // initialize 

const string Knight::whiteKnightFilename = IMG_PIECES_DIR + "wn.png";
const string Knight::blackKnightFilename = IMG_PIECES_DIR + "bn.png";

using namespace std;


Knight::~Knight() {
}

Knight::Knight(PieceColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == PieceColor::WHITE ? whiteKnightFilename : blackKnightFilename);

	if (getColor() != PieceColor::WHITE && getColor() != PieceColor::BLACK) {
		cerr << "Wrong color passed to Knight constructor !" << endl;
	}

	int counter = getColor() == PieceColor::WHITE ? whiteKnightCounter : blackKnightCounter;	// get correct Knight counter to infere correct position
	int yRow = getColor() == PieceColor::WHITE ? 7 : 0;									// spawn Knights on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = counter == 0 ? 1 * CANVAS_WIDTH / 8 : 6 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);
	Position boardPos = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(boardPos);

	cout << "setting " << name << " initial position to " << getInitialPosInBoard() << endl;
	
	// increment number of created knights
	getColor() == PieceColor::WHITE ? Knight::whiteKnightCounter++ : Knight::blackKnightCounter++;
}

vector<Position> Knight::calcMoves() {

	vector<Position> vec;
	Position curr = getCurrPosInBoard();

	/* right */
	vec.push_back(Position(curr.x + 2, curr.y + 1));
	vec.push_back(Position(curr.x + 2, curr.y - 1));

	/* left */
	vec.push_back(Position(curr.x - 2, curr.y + 1));
	vec.push_back(Position(curr.x - 2, curr.y - 1));

	/* down */
	vec.push_back(Position(curr.x + 1, curr.y + 2));
	vec.push_back(Position(curr.x - 1, curr.y + 2));

	/* up */
	vec.push_back(Position(curr.x + 1, curr.y - 2));
	vec.push_back(Position(curr.x - 1, curr.y - 2));

	return vec;
}