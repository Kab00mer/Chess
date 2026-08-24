#ifndef LOCAL_GAME_H
#define LOCAL_GAME_H

#include "../resources/screen.h"
#include "../resources/chess_board.h"

#include <set>

class LocalGame : public Screen {
	public:
		LocalGame();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*) override;
	
	private:
		void renderHighlightAt(const SDL_FRect&, const size_t, const size_t, const size_t) const;
		Coord getCoordFromMouse() const;

		SDL_FRect leftBoard[8][8];
		SDL_FRect rightBoard[8][8];

		ChessBoard board;

		Coord selectedSquare;

		SDL_FRect promotionScreen[4];
		bool inPromotionScreen;

		Piece pieceBeingHeld;

		Color whoseTurnIsIt;

		Move previousMove;
		std::set<Coord> possibleMoves;
};

#endif
