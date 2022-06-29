#pragma once
#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"
#include <string>

class Bishop : public ChessPiece {

public:
	Bishop(PieceColor color = PieceColor::NONE, SDL_Renderer* rend = nullptr, Position initialPos = Position{ 0,0 }, PieceSize size = PieceSize{ 0,0 }, string colorLetter = "", string pieceLetter = "");
	~Bishop();
	static int whiteBishopCounter, blackBishopCounter; // to count number of created Bishops and infere its position
	string colorLetter;
	string pieceLetter;
	string extension;
};
#endif // !BISHOP_H#pragma once
