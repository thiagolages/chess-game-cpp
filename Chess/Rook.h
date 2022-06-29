#pragma once
#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"
#include <string>

class Rook : public ChessPiece {

public:
	Rook(PieceColor color = PieceColor::NONE, SDL_Renderer* rend = nullptr, Position initialPos = Position{ 0,0 }, PieceSize size = PieceSize{ 0,0 }, string colorLetter = "", string pieceLetter = "");
	~Rook();
	static int whiteRookCounter, blackRookCounter; // to count number of created rooks and infere its position
	string colorLetter;
	string pieceLetter;
	string extension;
};
#endif // !ROOK_H