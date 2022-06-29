#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"
#include <string>

class Pawn : public ChessPiece {

public:
	Pawn(PieceColor color=PieceColor::NONE, SDL_Renderer *rend=nullptr, Position initialPos = Position{ 0,0 }, PieceSize size = PieceSize{ 0,0 }, string colorLetter = "", string pieceLetter = "");
	~Pawn();
	static int whitePawnCounter, blackPawnCounter; // to count number of created pawns and infere its position

	string colorLetter;
	string pieceLetter;
	string extension;
	Position initialPos;
	PieceSize size;
};
#endif // !PAWN_H