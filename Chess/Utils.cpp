#include"Utils.h"

bool isWithinBoardLimits(Position xyPos) {
	return (xyPos.x >= 0 && xyPos.x < horizontalSquares
		&& xyPos.y >= 0 && xyPos.y < verticalSquares);
}

bool isWithinBoardLimits(int x, int y) {
	return (x >= 0 && x < horizontalSquares
		&& y >= 0 && y < verticalSquares);
}

//
//const int GAME_FPS = 60;
//const int CANVAS_WIDTH = 800;
//const int CANVAS_HEIGHT = 800;
//
//const int horizontalSquares = 8;
//const int verticalSquares	= 8;
//
////string IMG_PIECES_DIR = "images/pieces/";
////string IMG_BOARDS_DIR = "images/boards/";
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
//ostream& operator<< (ostream& out, const PieceColor color) {
//	
//	switch (color){
//		case PieceColor::WHITE:
//			out << "WHITE";
//			break;
//		case PieceColor::BLACK:
//			out << "BLACK";
//			break;
//		case PieceColor::NONE:
//			out << "NONE";
//			break;
//		default:
//			break;
//	}
//	return out;
//}