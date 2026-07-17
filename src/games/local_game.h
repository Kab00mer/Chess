#ifndef LOCAL_GAME_H
#define LOCAL_GAME_H

#include "../resources/screen.h"

#include <set>

class LocalGame : public Screen {
	public:
		LocalGame();
		void run();
	
	private:
		void renderHighlightAt(const SDL_FRect&, const size_t, const size_t, const size_t) const;
		Coord getCoordFromMouse() const;

		SDL_FRect whitesBoard[8][8];
		SDL_FRect blacksBoard[8][8];

		Coord selectedSquare;

		SDL_FRect promotionScreen[4];
		bool inPromotionScreen;

		Piece pieceBeingHeld;

		Color whoseTurnIsIt;

		Move previousMove;
		std::set<Coord> possibleMoves;
};

#endif
