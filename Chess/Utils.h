#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <SDL.h>
#include"ChessElement.h"
#include "Piece.h"

using namespace std;

extern const int GAME_FPS		;
extern const int CANVAS_WIDTH	;
extern const int CANVAS_HEIGHT	;
extern const int horizontalSquares;
extern const int verticalSquares  ;
inline static const string IMG_PIECES_DIR = "images/pieces/";
inline static const string IMG_BOARDS_DIR = "images/boards/";

ostream& operator<< (ostream& out, const SDL_Rect* rec);
ostream& operator<< (ostream& out, const ChessElementColor color);

#endif // !UTILS_H