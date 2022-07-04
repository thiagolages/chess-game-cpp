#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <SDL.h>
#include"ChessElement.h"
#include "Piece.h"

using namespace std;

const int GAME_FPS			= 60 ;
const int CANVAS_WIDTH		= 800;
const int CANVAS_HEIGHT		= 800;
const int horizontalSquares = 8;
const int verticalSquares	= 8;
const string IMG_PIECES_DIR		= "images/pieces/";
const string IMG_BOARDS_DIR		= "images/boards/";

//
//ostream& operator<< (ostream& out, const SDL_Rect* rec) {
//	if (rec == nullptr) {
//		out << "NULLPTR";
//		return out;
//	}
//	out << "[" << rec->x << "," << rec->y << "," << rec->w << "," << rec->h << "]";
//	return out;
//}
//
//ostream& operator<< (ostream& out, const ChessElementColor color) {
//
//	switch (color) {
//	case ChessElementColor::WHITE:
//		out << "WHITE";
//		break;
//	case ChessElementColor::BLACK:
//		out << "BLACK";
//		break;
//	case ChessElementColor::NONE:
//		out << "NONE";
//		break;
//	default:
//		break;
//	}
//	return out;
//}

#endif // !UTILS_H