#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"

class ChessBoard {
	public :
		ChessBoard();
		

	private :
		Pieces* board[8][8];
};

#endif
