#include "board.h"
#include <iostream>

ChessBoard::ChessBoard() {
	//creates the classic chessboard setup
	for (size_t i = 0; i < 8; ++i) {
		squares[1][i] = std::unique_ptr<ChessPiece>(new Pawn('w'));
		squares[6][i] = std::unique_ptr<ChessPiece>(new Pawn('b'));
	}
			
	squares[0][0] = std::unique_ptr<ChessPiece>(new Rook('w'));
	squares[0][7] = std::unique_ptr<ChessPiece>(new Rook('w'));
	squares[7][0] = std::unique_ptr<ChessPiece>(new Rook('b'));
	squares[7][7] = std::unique_ptr<ChessPiece>(new Rook('b'));

	squares[0][1] = std::unique_ptr<ChessPiece>(new Knight('w'));
	squares[0][6] = std::unique_ptr<ChessPiece>(new Knight('w'));
	squares[7][1] = std::unique_ptr<ChessPiece>(new Knight('b'));
	squares[7][6] = std::unique_ptr<ChessPiece>(new Knight('b'));

	squares[0][2] = std::unique_ptr<ChessPiece>(new Bishop('w'));
	squares[0][5] = std::unique_ptr<ChessPiece>(new Bishop('w'));
	squares[7][2] = std::unique_ptr<ChessPiece>(new Bishop('b'));
	squares[7][5] = std::unique_ptr<ChessPiece>(new Bishop('b'));

	squares[0][3] = std::unique_ptr<ChessPiece>(new Queen('w'));
	squares[7][3] = std::unique_ptr<ChessPiece>(new Queen('b'));

	squares[0][4] = std::unique_ptr<ChessPiece>(new King('w'));
	squares[7][4] = std::unique_ptr<ChessPiece>(new King('b'));
}

std::string ChessBoard::getPieceAt(const size_t x, const size_t y) const {
	std::cout << x << y;
	std::cout << (squares[x][y] ? "STRING:" + squares[x][y]->returnColorAndType() : "empty");
	std::cout << '\n';
	return squares[x][y] ? squares[x][y]->returnColorAndType() : "";
}

bool ChessBoard::CheckForCheck() const {
	return false;
}

bool ChessBoard::CheckForMate() const {
	return false;
}
