#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <memory>

class ChessBoard {
	public :
		ChessBoard();

		std::pair<PieceType, Color> returnPieceAt(std::pair<size_t, size_t>) const;
		bool CheckForCheck() const;
		bool CheckForMate() const;

	private :
		std::unique_ptr<ChessPiece> squares[8][8];
};

#endif
