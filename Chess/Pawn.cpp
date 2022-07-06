#include "Utils.h"
#include "Pawn.h"
#include <iostream>

int Pawn::whitePawnCounter = 0; // initialize 
int Pawn::blackPawnCounter = 0; // initialize 

using namespace std;


Pawn::~Pawn() {
}

Pawn::Pawn(PieceColor color, string name) 
	: Piece(color, "", nullptr, nullptr, name) {

	imgFilename = (getColor() == PieceColor::WHITE ? whitePawnFilename : blackPawnFilename);
	if (getColor() != PieceColor::WHITE && getColor() != PieceColor::BLACK) {
		cerr << "Wrong color passed to Pawn constructor !" << endl;
	}
			
	int counter	= getColor() == PieceColor::WHITE ? whitePawnCounter : blackPawnCounter;// get correct pawn counter to infere correct position
	int yRow	= getColor() == PieceColor::WHITE ?	6 : 1;								// spawn pawns on 7nd or 2th row (indexes 6 or 1)

	Position pos;
	pos.x	= counter * CANVAS_WIDTH / 8;
	pos.y	=  yRow   * CANVAS_HEIGHT/8;

	setCurrPosInPixels(pos);
	Position boardPos = { pos.x / Piece::pieceSize.w, pos.y / Piece::pieceSize.h };
	setInitialPosInBoard(boardPos);

	cout << "setting " << name << " initial position to " << getInitialPosInBoard() << endl;

	// increment number of created pawns
	getColor() == PieceColor::WHITE ? Pawn::whitePawnCounter++ : Pawn::blackPawnCounter++;
}

vector<Position> Pawn::calcMoves() {
	vector<Position> vec;
	
	Position curr = getCurrPosInBoard();
	// moving up (white) or down (black) the board
	int dy = (getColor() == PieceColor::WHITE ? -1 : 1);
	
	// normal move
	if (isWithinBoardLimits(curr.x, curr.y + dy))vec.push_back(Position(curr.x, curr.y + dy));
	
	// if pawn hasn't been moved, we can move it 2 squares
	if (!hasBeenMovedOnce) {
		if (isWithinBoardLimits(curr.x, curr.y + dy * 2))vec.push_back(Position(curr.x, curr.y + dy*2));
	}
	return vec;
}