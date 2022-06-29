#include "Utils.h"
#include "Queen.h"
#include <iostream>

using namespace std;

Queen::~Queen() {

}
Queen::Queen(PieceColor color, SDL_Renderer* rend, Position initialPos, PieceSize size, string colorLetter, string pieceLetter)
{
	this->rend = rend;
	this->color = color;
	this->initialPos = initialPos;
	this->extension = ".png";
	this->pieceLetter = "q";
	this->colorLetter = (this->color == PieceColor::WHITE ? "w" : "b");
	this->imgFilename = IMG_PIECES_DIR + this->colorLetter + this->pieceLetter + extension;

	if (this->color != PieceColor::WHITE && this->color != PieceColor::BLACK) {
		cerr << "Wrong color passed to Queen constructor !" << endl;
	}

	int yRow = this->color == PieceColor::WHITE ? 7 : 0;									// spawn Queens on 8nd or 1th row (indexes 7 or 0)

	this->initialPos.x = 3 * CANVAS_WIDTH / 8;
	this->initialPos.y = yRow * CANVAS_HEIGHT / 8;

	this->srcRect = nullptr; // to select all contents of the src image

	this->dstRect = new SDL_Rect{
			this->initialPos.x,
			this->initialPos.y,
			pieceSize.w,
			pieceSize.h };

}