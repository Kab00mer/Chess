#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"

class ChessBoard {
	public :
		ChessBoard(bool white = true);
		~ChessBoard();

		std::pair<char, char> getPieceAt(const size_t, const size_t) const;
		bool isUserWhite() const;

		bool movePiece(int, int, int, int);
		bool checkForCheck() const;
		bool checkForMate() const;

		void printBoard() const;

	private :
		ChessPiece* squares[8][8];
		bool userIsWhite;
};

#endif
