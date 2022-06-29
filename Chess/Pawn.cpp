#include "Utils.h"
#include "Pawn.h"
#include <iostream>

int Pawn::whitePawnCounter = 0; // initialize 
int Pawn::blackPawnCounter = 0; // initialize 

using namespace std;

Pawn::~Pawn() {

}

Pawn::Pawn(PieceColor color, SDL_Renderer* rend, Position initialPos, PieceSize size, string colorLetter, string pieceLetter) 
{
	this->rend = rend;
	this->color = color;
	this->initialPos = initialPos;
	this->extension = ".png";
	this->pieceLetter = "p";
	this->colorLetter = (this->color == PieceColor::WHITE ? "w" : "b");
	this->imgFilename = IMG_PIECES_DIR + this->colorLetter + this->pieceLetter + extension;

	if (this->color != PieceColor::WHITE && this->color != PieceColor::BLACK) {
		cerr << "Wrong color passed to Pawn constructor !" << endl;
	}
			
	int counter	= this->color == PieceColor::WHITE ? whitePawnCounter : blackPawnCounter;	// get correct pawn counter to infere correct position
	int yRow	= this->color == PieceColor::WHITE ?	6 : 1;								// spawn pawns on 7nd or 2th row (indexes 6 or 1)

	this->initialPos.x	= counter * CANVAS_WIDTH / 8;
	this->initialPos.y	=  yRow   * CANVAS_HEIGHT/8;

	this->srcRect = nullptr; // to select all contents of the src image
	
	this->dstRect = new SDL_Rect{
			this->initialPos.x,
			this->initialPos.y,
			pieceSize.w,
			pieceSize.h };

	// increment number of created pawns
	this->color == PieceColor::WHITE ? Pawn::whitePawnCounter++ :	Pawn::blackPawnCounter++;
}