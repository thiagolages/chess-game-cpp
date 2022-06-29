#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <SDL.h>
#include <iostream>
#include <string>

using namespace std;	

enum class PieceType  { NONE, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
enum class PieceColor { WHITE, BLACK, NONE };

typedef struct Position {
	int x, y;
}Position;

typedef struct PieceSize {
	int w, h;
}PieceSize;

class ChessPiece {
	
public:
	ChessPiece();
	ChessPiece(PieceColor color, string imgFilename, SDL_Renderer* rend, SDL_Rect* srcRect=NULL, SDL_Rect* dstRect=NULL);
	~ChessPiece();
	void render();

protected:
	SDL_Renderer	*rend;
	SDL_Rect		*srcRect, *dstRect;
	SDL_Texture		*texture;
	SDL_Surface		*image_surface;
	string			 imgFilename;
	PieceColor		 color;
	Position		 initialPos;

	//string imgFileExtension;
	
};
#endif // !CHESS_PIECE_H