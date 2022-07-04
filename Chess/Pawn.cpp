#include "Utils.h"
#include "Pawn.h"
#include <iostream>

int Pawn::whitePawnCounter = 0; // initialize 
int Pawn::blackPawnCounter = 0; // initialize 

using namespace std;

Pawn::~Pawn() {
}

Pawn::Pawn(ChessElementColor color, string name) 
	: Piece(color, "", nullptr, nullptr, name){

	imgFilename = (getColor() == ChessElementColor::WHITE ? whitePawnFilename : blackPawnFilename);
	if (getColor() != ChessElementColor::WHITE && getColor() != ChessElementColor::BLACK) {
		cerr << "Wrong color passed to Pawn constructor !" << endl;
	}
			
	int counter	= getColor() == ChessElementColor::WHITE ? whitePawnCounter : blackPawnCounter;// get correct pawn counter to infere correct position
	int yRow	= getColor() == ChessElementColor::WHITE ?	6 : 1;								// spawn pawns on 7nd or 2th row (indexes 6 or 1)

	Position pos;
	pos.x	= counter * CANVAS_WIDTH / 8;
	pos.y	=  yRow   * CANVAS_HEIGHT/8;

	setCurrPosInPixels(pos);

	// increment number of created pawns
	getColor() == ChessElementColor::WHITE ? Pawn::whitePawnCounter++ : Pawn::blackPawnCounter++;
}