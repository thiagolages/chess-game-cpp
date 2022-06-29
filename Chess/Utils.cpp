#include"Utils.h"

const int GAME_FPS = 60;
const int CANVAS_WIDTH = 800;
const int CANVAS_HEIGHT = 800;

const int horizontalSquares = 8;
const int verticalSquares	= 8;
const string IMG_PIECES_DIR = "images/pieces/";
const string IMG_BOARDS_DIR = "images/boards/";
const PieceSize pieceSize	= { CANVAS_WIDTH / horizontalSquares, CANVAS_HEIGHT / verticalSquares };

ostream& operator<< (ostream& out, const SDL_Rect* rec) {
	if (rec == nullptr) {
		out << "NULLPTR";
		return out;
	}
	out << "[" << rec->x << "," << rec->y << "," << rec->w << "," << rec->h << "]";
	return out;
}