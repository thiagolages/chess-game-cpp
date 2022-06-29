#pragma once
#ifndef KING_H
#define KING_H

#include "ChessPiece.h"
#include <string>

class King : public ChessPiece {

public:
	King(PieceColor color = PieceColor::NONE, SDL_Renderer* rend = nullptr, Position initialPos = Position{ 0,0 }, PieceSize size = PieceSize{ 0,0 }, string colorLetter = "", string pieceLetter = "");
	~King();
	string colorLetter;
	string pieceLetter;
	string extension;
};
#endif // !KING_H#pragma once
