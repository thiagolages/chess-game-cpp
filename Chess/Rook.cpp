#include "Utils.h"
#include "Rook.h"
#include <iostream>

int Rook::whiteRookCounter = 0; // initialize 
int Rook::blackRookCounter = 0; // initialize 

using namespace std;

Rook::~Rook() {

}
Rook::Rook(PieceColor color, SDL_Renderer* rend, Position initialPos, PieceSize size, string colorLetter, string pieceLetter)
{
	this->rend = rend;
	this->color = color;
	this->initialPos = initialPos;
	this->extension = ".png";
	this->pieceLetter = "r";
	this->colorLetter = (this->color == PieceColor::WHITE ? "w" : "b");
	this->imgFilename = IMG_PIECES_DIR + this->colorLetter + this->pieceLetter + extension;

	if (this->color != PieceColor::WHITE && this->color != PieceColor::BLACK) {
		cerr << "Wrong color passed to Rook constructor !" << endl;
	}

	int counter = this->color == PieceColor::WHITE ? whiteRookCounter : blackRookCounter;	// get correct rook counter to infere correct position
	int yRow	= this->color == PieceColor::WHITE ? 7 : 0;									// spawn rooks on 8nd or 1th row (indexes 7 or 0)

	this->initialPos.x = counter == 1 ? 0 : 7 * CANVAS_WIDTH / 8;
	this->initialPos.y = yRow * CANVAS_HEIGHT / 8;

	this->srcRect = nullptr; // to select all contents of the src image

	this->dstRect = new SDL_Rect{
			this->initialPos.x,
			this->initialPos.y,
			pieceSize.w,
			pieceSize.h };

	// increment number of created rooks
	this->color == PieceColor::WHITE ? Rook::whiteRookCounter++ : Rook::blackRookCounter++;
}