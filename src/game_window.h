#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "window.h"
#include "chess_board.h"

#include <string>
#include <map>

class GameWindow : public Window {
	public:
		GameWindow();
		virtual ~GameWindow();

		void run() override;

	protected:
		/*
		void renderBoardAt();
		virtual Coord convertMousePosToCoord() const;
		std::string convertPieceToCoord() const;
		*/
	
	private:
		ChessBoard* board;
		std::map<std::string, SDL_Texture*> pieceTextures;

		Coord selectedSquare;
		bool gameFinished;
		float squareSize;
};

#endif
