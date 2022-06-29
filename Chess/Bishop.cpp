#include "Utils.h"
#include "Bishop.h"
#include <iostream>

int Bishop::whiteBishopCounter = 0; // initialize 
int Bishop::blackBishopCounter = 0; // initialize 

using namespace std;

Bishop::~Bishop() {

}
Bishop::Bishop(PieceColor color, SDL_Renderer* rend, Position initialPos, PieceSize size, string colorLetter, string pieceLetter)
{
	this->rend = rend;
	this->color = color;
	this->initialPos = initialPos;
	this->extension = ".png";
	this->pieceLetter = "b";
	this->colorLetter = (this->color == PieceColor::WHITE ? "w" : "b");
	this->imgFilename = IMG_PIECES_DIR + this->colorLetter + this->pieceLetter + extension;

	if (this->color != PieceColor::WHITE && this->color != PieceColor::BLACK) {
		cerr << "Wrong color passed to Bishop constructor !" << endl;
	}

	int counter = this->color == PieceColor::WHITE ? whiteBishopCounter : blackBishopCounter;	// get correct Bishop counter to infere correct position
	int yRow = this->color == PieceColor::WHITE ? 7 : 0;									// spawn Bishops on 8nd or 1th row (indexes 7 or 0)

	this->initialPos.x = counter == 1 ? 2 * CANVAS_WIDTH / 8 : 5 * CANVAS_WIDTH / 8;
	this->initialPos.y = yRow * CANVAS_HEIGHT / 8;

	this->srcRect = nullptr; // to select all contents of the src image

	this->dstRect = new SDL_Rect{
			this->initialPos.x,
			this->initialPos.y,
			pieceSize.w,
			pieceSize.h };

	// increment number of created Bishops
	this->color == PieceColor::WHITE ? Bishop::whiteBishopCounter++ : Bishop::blackBishopCounter++;
}