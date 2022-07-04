#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Piece.h"
#include "Utils.h"

using namespace std;

//string Piece::pieceBaseFileDir		= "images/pieces/";
//string Piece::pieceBaseFileExtension	= ".png";

Piece::Piece(ChessElementColor color, string imgFilename, SDL_Rect* srcRect, SDL_Rect* dstRect, string name)
	: ChessElement(color, imgFilename, nullptr, srcRect, dstRect, name), currPosInBoard(Position()){
}

Piece::~Piece() {
	cout << "destructor() Piece" << name << endl;
}

void Piece::setSrcRect(SDL_Rect *srcRect) {
	delete this->srcRect;
	this->srcRect = srcRect;
}

void Piece::setDstRect(SDL_Rect *dstRect) {
	delete this->dstRect;
	this->dstRect = dstRect;
}

void Piece::setCurrPosInPixels(Position pos) {

	if (pos.x < 0 || pos.x >= CANVAS_WIDTH || pos.y < 0 || pos.y >= CANVAS_HEIGHT) {
		cerr << "Wrong positioning of the piece " << imgFilename << "inside setCurrPosInPixels(). ";
		cerr << "Received (" << pos.x << ", " << pos.y << ") as argument" << endl;
		return;
	}

	this->currPosInPixels = pos;
	
	this->currPosInBoard = {
		pos.x / pieceSize.w,
		pos.y / pieceSize.h
	};

	// always keep dstRect updated so it renders in the right place
	SDL_Rect* newRect = new SDL_Rect{
			pos.x,
			pos.y,
			pieceSize.w,
			pieceSize.h };

	setDstRect(newRect);
}

void Piece::setCurrPosInBoard(Position pos) {

	if (pos.x < 0 || pos.x >= horizontalSquares || pos.y < 0 || pos.y >= verticalSquares) {
		cerr << "Wrong positioning of the piece inside setCurrPosInBoard(). ";
		cerr << "Received (" << pos.x << ", " << pos.y << ") as argument" << endl;
		return;
	}

	this->currPosInPixels = pos;

	this->currPosInBoard = {
		pos.x / pieceSize.w,
		pos.y / pieceSize.h
	};

	// always keep dstRect updated so it renders in the right place
	setDstRect(new SDL_Rect{
			pos.x,
			pos.y,
			pieceSize.w,
			pieceSize.h });
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

Position Piece::getCurrPosInPixels() {
	return this->currPosInPixels;
}