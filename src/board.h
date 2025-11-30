#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <memory>

class ChessBoard {
	public :
		ChessBoard();

		std::string getPieceAt(const size_t, const size_t) const;
		bool CheckForCheck() const;
		bool CheckForMate() const;

	private :
		std::unique_ptr<ChessPiece> squares[8][8];
};

#endif
