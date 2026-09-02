#ifndef LOCAL_GAME_H
#define LOCAL_GAME_H

#include "../resources/screen.h"
#include "../resources/chess_board.h"

#include <set>

class LocalGame : public Screen {
	public:
		LocalGame();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*, const std::map<std::string, SDL_Texture*>&) override;
	
	private:
		void lookForMouseInBoard(size_t&, size_t&, bool);
		void renderHighlightAt(const SDL_FRect&, const size_t, const size_t, 
				const size_t, SDL_Renderer*) const;

		SDL_FRect leftBoard[8][8];
		SDL_FRect rightBoard[8][8];

		ChessBoard game;

		Coord selectedSquare;
		SDL_FPoint mouse;

		SDL_FRect promotionScreen[4];
		bool inPromotionScreen;

		Piece pieceBeingHeld;

		Color whoseTurnIsIt;

		std::pair<Coord, Coord> previousMove;
		std::set<Coord> possibleMoves;
};

#endif
