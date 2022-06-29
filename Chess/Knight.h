#pragma once
#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"
#include <string>

class Knight : public ChessPiece {

public:
	Knight(PieceColor color = PieceColor::NONE, SDL_Renderer* rend = nullptr, Position initialPos = Position{ 0,0 }, PieceSize size = PieceSize{ 0,0 }, string colorLetter = "", string pieceLetter = "");
	~Knight();
	static int whiteKnightCounter, blackKnightCounter; // to count number of created Knights and infere its position
	string colorLetter;
	string pieceLetter;
	string extension;
};
#endif // !KNIGHT_H