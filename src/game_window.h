#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "window.h"
#include "chess_board.h"

#include <string>
#include <map>

class GameWindow : public Window {
	public:
		GameWindow(const size_t width = 0, const size_t height = 0);
		void run() override;

	protected:
		void renderBoardAt(const size_t, const size_t) const;
		void renderLostPiecesOf(const Color) const;

		std::map<std::pair<Color, PieceType>, SDL_Texture*> pieceTextures;
		ChessBoard* board;
		float squareSize;
	
	private:
		Coord selectedSquare;
		bool gameFinished;
};

#endif
