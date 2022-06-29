#include "Utils.h"
#include "Pawn.h"
#include <iostream>

int Pawn::whitePawnCounter = 0; // initialize 
int Pawn::blackPawnCounter = 0; // initialize 

using namespace std;

Pawn::~Pawn() {

}

Pawn::Pawn(PieceColor color, SDL_Renderer* rend, Position initialPos, PieceSize size, string colorLetter, string pieceLetter): 
	initialPos(initialPos), size(size)
{
	this->rend = rend;
	this->color = color;

	cout << "rend inside Pawn() == nullptr? " << (rend == nullptr ? "yes" : "no") << endl;
	cout << "calling pawn(color, render) constructor" << endl;
	if (color != PieceColor::WHITE && color != PieceColor::BLACK) {
		cerr << "Wrong color passed to Pawn constructor !" << endl;
	}
	extension = ".png";
	pieceLetter = "p";
	colorLetter = (color == PieceColor::WHITE ? "w" : "b");
	imgFilename = IMG_PIECES_DIR + colorLetter + pieceLetter + extension;
	

	// get correct pawn counter to infere correct position
	int counter		= color == PieceColor::WHITE ? whitePawnCounter : blackPawnCounter;
	// spawn pawns on 7nd or 2th row (indexes 6 or 1)
	int yRow = color == PieceColor::WHITE ? 6 : 1;

	initialPos.x	= counter * CANVAS_WIDTH / 8;
	initialPos.y	=  yRow   * CANVAS_HEIGHT/8;
	size.w = CANVAS_WIDTH / 8;
	size.h = CANVAS_HEIGHT / 8;

	srcRect = nullptr;
	//dstRect = nullptr;
	dstRect = new SDL_Rect{
			initialPos.x,
			initialPos.y,
			size.w,
			size.h };

	// increment number of created pawns
	color == PieceColor::WHITE ? Pawn::whitePawnCounter++ :	Pawn::blackPawnCounter++;
	cout << "imgFileName inside Pawn(...) = " << imgFilename << endl;
	cout << "inside Pawn(...)" << endl;
	cout << "srcRect = " << srcRect << ", dstRect = " << dstRect << endl;
}