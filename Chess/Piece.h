#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include "Utils.h"
#include "ChessElement.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;	

enum class PieceType  { NONE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

typedef struct Position {
	int x, y;
	Position() { x = -1; y = -1; }
	Position(int xArg, int yArg) { x = xArg; y = yArg; }
	inline friend bool operator== (const Position& lhs, const Position& rhs) {
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	}
	inline friend ostream& operator<< (ostream& out, const Position& pos) {
		out << "(" << pos.x << "," << pos.y << ")" << endl;
		return out;
	}
}Position;

typedef struct PieceSize {
	int w, h;
	PieceSize() { w = -1; h = -1; }
	PieceSize(int wArg, int hArg) { w = wArg; h = hArg;}
}PieceSize;

// we have to inherit publicly so all public members remain public (in order to be used by Game.cpp
class Piece : public ChessElement { 
	
public:
	Piece(ChessElementColor color = ChessElementColor::NONE, string imgFilename = "", SDL_Rect* srcRect = NULL, SDL_Rect* dstRect = NULL, string name = "");
	~Piece();
	void setSrcRect(SDL_Rect* srcRect);
	void setDstRect();
	void setCurrPosInPixels(Position pos, bool updatePosInBoard = true);
	void setCurrPosInBoard(Position);
	void setInitialPosInBoard(Position);
	SDL_Rect* getSrcRect();
	SDL_Rect* getDstRect();
	ChessElementColor getColor();
	Position getCurrPosInPixels();
	Position getCurrPosInBoard();
	Position getInitialPosInBoard();
	bool isLegalMove(Position);
	void capturedPieceRoutine();
	virtual vector<Position> calcMoves() =0; // derived classes must provide implementation

public:
	inline static const PieceSize	 pieceSize = { 100, 100 }; // { CANVAS_WIDTH / horizontalSquares, CANVAS_HEIGHT / verticalSquares };
	bool			hasBeenMovedOnce;

protected:
	Position		currPosInBoard; // with respect to the board. (0,0) being 1st row, 1st column
	Position		currPosInPixels; // with respect to the window
	Position		initialPosInBoard;
	
};
#endif // !CHESS_PIECE_H