#ifndef BOARD_H
#define BOARD_H

#include <set>
#include "pieces.h"

class ChessBoard {
	public :
		ChessBoard(bool white = true);
		~ChessBoard();

		bool isUserWhite() const;

		std::pair<char, char> getPieceAt(const size_t, const size_t) const;
		std::set<std::pair<int, int>> getMovesForPiece(const size_t, const size_t) const;

		void movePiece(int, int, int, int);
		bool checkForCheck() const;
		bool checkForMate() const;


		void printBoard() const;
		void printCollisionBoard() const;

	private :
		ChessPiece* squares[8][8];
		char collisionMap[8][8];
		bool userIsWhite;
};

#endif
