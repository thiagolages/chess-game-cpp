#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include "AllChessPieces.h"
#include "Board.h"
#include <vector>

using namespace std;

extern const int maxNumPawns;
extern const int maxNumMiddlePieces;

class Game {

public:
	Game(bool closeGame=false, SDL_Renderer* rend=nullptr, SDL_Window* window=nullptr);
	~Game();
	void init();
	void show(); // actually show render on the screen
	void reset();
	bool isYourTurn();
	void changeTurns();
	void gameSDL_init();
	void renderAllElements();
	void render					(ChessElement* ce);
	void renderCircle			(Position boardPos);
	void renderLegalMoves		(Piece* piece);
	void handleEvents			(SDL_Event &event);
	void handleKeyDown			(SDL_Event &event);
	void handleMouseMotion		(SDL_Event &event);
	void handleMouseButtonUp	(SDL_Event& event);
	bool isDifferentColor		(Piece* p1, Piece* p2);
	bool isDifferentPiece		(Piece* p1, Piece* p2);
	void drawCircle				(Position center, int radius);
	void handleMouseButtonDown	(SDL_Event& event);
	Piece* pixelPositionToPiece	(const Position pos);
	Piece* pixelPositionToPiece	(const int& x, const int& y);
	Piece* boardPositionToPiece (const Position pos);
	bool isLegalMove			(Piece* currClickedPiece, Position boardPos);
	bool pieceCanMakeMove(Piece* piece, Position boardPos);
	static Position pixelPosToBoardPos	(Position pixelPos);
	bool theresAPieceIn			(Position boardPos);
	bool theresAPieceBetween	(Piece* piece, Position boardPos);
	bool isInSameDiagonal		(Position p1, Position p2);
	bool isCheckIfIMove			(Piece* piece, Position boardPos);
	bool isInSameColumn			(Position p1, Position p2);
	bool isInSameRow			(Position p1, Position p2);
	bool isKingSafeAfterMove		(Piece* piece, Position boardPos);
	SDL_Renderer* rend;
	bool closeGame;
	bool mouseIsPressed;

private:
	Board* board;
	vector<Piece*>	allPieces;
	SDL_Window* window;
	SDL_Texture* windowTexture;
	Piece *currClickedPiece;
	PieceColor colorTurn;
	
	//SDL_Rect* calcRenderPosition(ChessElement element);	

};

#endif // !GAME_H