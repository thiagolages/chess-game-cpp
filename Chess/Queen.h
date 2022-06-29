#pragma once
#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include <string>

class Queen : public ChessPiece {

public:
	Queen(PieceColor color = PieceColor::NONE, SDL_Renderer* rend = nullptr, Position initialPos = Position{ 0,0 }, PieceSize size = PieceSize{ 0,0 }, string colorLetter = "", string pieceLetter = "");
	~Queen();
	string colorLetter;
	string pieceLetter;
	string extension;
};
#endif // !QUEEN_H#pragma once
