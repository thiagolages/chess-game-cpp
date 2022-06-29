#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <string>
#include <SDL.h>
#include "ChessPiece.h"

using namespace std;

extern const int GAME_FPS		;
extern const int CANVAS_WIDTH	;
extern const int CANVAS_HEIGHT	;
extern const int horizontalSquares;
extern const int verticalSquares  ;
extern const string IMG_PIECES_DIR;
extern const string IMG_BOARDS_DIR;
extern const PieceSize pieceSize;

ostream& operator<< (ostream& out, const SDL_Rect* rec);

#endif // !CONSTANTS_H