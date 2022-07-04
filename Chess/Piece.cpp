#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Piece.h"
#include "Utils.h"

using namespace std;

//string Piece::pieceBaseFileDir		= "images/pieces/";
//string Piece::pieceBaseFileExtension	= ".png";

Piece::Piece(ChessElementColor color, string imgFilename, SDL_Rect* srcRect, SDL_Rect* dstRect, string name)
	: ChessElement(color, imgFilename, nullptr, srcRect, dstRect, name), 
	  currPosInBoard(Position()), initialPosInBoard(Position()), hasBeenMovedOnce(false) {

}

Piece::~Piece() {
}

bool Piece::isLegalMove(Position posInBoard) {
	if (posInBoard.x < 0 || posInBoard.x >= 8
	 || posInBoard.y < 0 || posInBoard.y >= 8) {
		return false;
	}
	// will be implemented later on each derived class
	return true;
}

void Piece::capturedPieceRoutine() {
	this->hasBeenCaptured = true;
	this->currPosInBoard  = { -1, -1 };
	this->currPosInPixels = { -1, -1 };
}

void Piece::setSrcRect(SDL_Rect *srcRect) {
	delete this->srcRect;
	this->srcRect = srcRect;
}

void Piece::setDstRect() {

	if (this->dstRect != nullptr) {
		delete this->dstRect; // delete current pointer
	}
	Position pos = getCurrPosInPixels();
	this->dstRect = new SDL_Rect{
			pos.x,
			pos.y,
			pieceSize.w,
			pieceSize.h };
}

void Piece::setCurrPosInPixels(Position pos, bool updatePosInBoard) {

	/*if (pos.x < 0 || pos.x >= CANVAS_WIDTH || pos.y < 0 || pos.y >= CANVAS_HEIGHT) {
		cerr << "Wrong positioning of the piece " << imgFilename << "inside setCurrPosInPixels(). ";
		cerr << "Received (" << pos.x << ", " << pos.y << ") as argument" << endl;
		return;
	}*/

	this->currPosInPixels = pos;
	
	if (updatePosInBoard) {
		this->currPosInBoard = {
			pos.x / Piece::pieceSize.w,
			pos.y / Piece::pieceSize.h
		};
	}

	// always keep dstRect updated so it renders in the right place
	setDstRect();
}

void Piece::setCurrPosInBoard(Position pos) {

	if (pos.x < 0 || pos.x >= horizontalSquares || pos.y < 0 || pos.y >= verticalSquares) {
		cerr << "Wrong positioning of the piece inside setCurrPosInBoard(). ";
		cerr << "Received (" << pos.x << ", " << pos.y << ") as argument" << endl;
		return;
	}

	this->currPosInBoard = pos;
	if (pos.x >= 0 && pos.y >= 0) {
		this->currPosInPixels = {
		pos.x * Piece::pieceSize.w,
		pos.y * Piece::pieceSize.h
		};

		// always keep dstRect updated so it renders in the right place
		setDstRect();
	}
	
}

void Piece::setInitialPosInBoard(Position pos) {

	if (pos.x < 0 || pos.x >= horizontalSquares || pos.y < 0 || pos.y >= verticalSquares) {
		cerr << "Wrong positioning of the piece inside setCurrPosInBoard(). ";
		cerr << "Received (" << pos.x << ", " << pos.y << ") as argument" << endl;
		return;
	}

	this->initialPosInBoard = {
		pos.x,
		pos.y
	};
}

SDL_Rect* Piece::getSrcRect() {
	return this->srcRect;
}

SDL_Rect* Piece::getDstRect() {
	return this->dstRect;
}

ChessElementColor Piece::getColor() {
	return this->color;
}

Position Piece::getCurrPosInBoard() { 
	return this->currPosInBoard; 
}

Position Piece::getInitialPosInBoard() {
	return this->initialPosInBoard;
}

Position Piece::getCurrPosInPixels() {
	return this->currPosInPixels;
}