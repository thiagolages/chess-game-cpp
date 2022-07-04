#include "Utils.h"
#include "Knight.h"
#include <iostream>

int Knight::whiteKnightCounter = 0; // initialize 
int Knight::blackKnightCounter = 0; // initialize 

const string Knight::whiteKnightFilename = IMG_PIECES_DIR + "wn.png";
const string Knight::blackKnightFilename = IMG_PIECES_DIR + "bn.png";

using namespace std;

Knight::~Knight() {
}

Knight::Knight(ChessElementColor color, string name)
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == ChessElementColor::WHITE ? whiteKnightFilename : blackKnightFilename);

	if (getColor() != ChessElementColor::WHITE && getColor() != ChessElementColor::BLACK) {
		cerr << "Wrong color passed to Knight constructor !" << endl;
	}

	int counter = getColor() == ChessElementColor::WHITE ? whiteKnightCounter : blackKnightCounter;	// get correct Knight counter to infere correct position
	int yRow = getColor() == ChessElementColor::WHITE ? 7 : 0;									// spawn Knights on 8nd or 1th row (indexes 7 or 0)

	Position pos;
	pos.x = counter == 0 ? 1 * CANVAS_WIDTH / 8 : 6 * CANVAS_WIDTH / 8;
	pos.y = yRow * CANVAS_HEIGHT / 8;

	setCurrPosInPixels(pos);

	// increment number of created knights
	getColor() == ChessElementColor::WHITE ? Knight::whiteKnightCounter++ : Knight::blackKnightCounter++;
}