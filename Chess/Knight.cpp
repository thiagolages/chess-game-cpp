#include "Utils.h"
#include "Knight.h"
#include <iostream>

int Knight::whiteKnightCounter = 0; // initialize 
int Knight::blackKnightCounter = 0; // initialize 

using namespace std;

Knight::~Knight() {

}
Knight::Knight(PieceColor color, SDL_Renderer* rend, Position initialPos, PieceSize size, string colorLetter, string pieceLetter)
{
	this->rend = rend;
	this->color = color;
	this->initialPos = initialPos;
	this->extension = ".png";
	this->pieceLetter = "n";
	this->colorLetter = (this->color == PieceColor::WHITE ? "w" : "b");
	this->imgFilename = IMG_PIECES_DIR + this->colorLetter + this->pieceLetter + extension;

	if (this->color != PieceColor::WHITE && this->color != PieceColor::BLACK) {
		cerr << "Wrong color passed to Knight constructor !" << endl;
	}

	int counter = this->color == PieceColor::WHITE ? whiteKnightCounter : blackKnightCounter;	// get correct Knight counter to infere correct position
	int yRow = this->color == PieceColor::WHITE ? 7 : 0;									// spawn Knights on 8nd or 1th row (indexes 7 or 0)

	this->initialPos.x = counter == 1 ? 1* CANVAS_WIDTH / 8 : 6 * CANVAS_WIDTH / 8;
	this->initialPos.y = yRow * CANVAS_HEIGHT / 8;

	this->srcRect = nullptr; // to select all contents of the src image

	this->dstRect = new SDL_Rect{
			this->initialPos.x,
			this->initialPos.y,
			pieceSize.w,
			pieceSize.h };

	// increment number of created Knights
	this->color == PieceColor::WHITE ? Knight::whiteKnightCounter++ : Knight::blackKnightCounter++;
}