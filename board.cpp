#include "board.h"

ChessBoard::ChessBoard() {
	for (int i = 0; i < 8; ++i) {
		squares[1][i] = std::unique_ptr<ChessPiece>(new Pawn(Color::White));
		squares[6][i] = std::unique_ptr<ChessPiece>(new Pawn(Color::Black));
	}
			
	squares[0][0] = std::unique_ptr<ChessPiece>(new Rook(Color::White));
	squares[0][7] = std::unique_ptr<ChessPiece>(new Rook(Color::White));
	squares[7][0] = std::unique_ptr<ChessPiece>(new Rook(Color::Black));
	squares[7][7] = std::unique_ptr<ChessPiece>(new Rook(Color::Black));

	squares[0][1] = std::unique_ptr<ChessPiece>(new Knight(Color::White));
	squares[0][6] = std::unique_ptr<ChessPiece>(new Knight(Color::White));
	squares[7][1] = std::unique_ptr<ChessPiece>(new Knight(Color::Black));
	squares[7][6] = std::unique_ptr<ChessPiece>(new Knight(Color::Black));

	squares[0][2] = std::unique_ptr<ChessPiece>(new Bishop(Color::White));
	squares[0][5] = std::unique_ptr<ChessPiece>(new Bishop(Color::White));
	squares[7][2] = std::unique_ptr<ChessPiece>(new Bishop(Color::Black));
	squares[7][5] = std::unique_ptr<ChessPiece>(new Bishop(Color::Black));

	squares[0][3] = std::unique_ptr<ChessPiece>(new Queen(Color::White));
	squares[7][3] = std::unique_ptr<ChessPiece>(new Queen(Color::White));

	squares[0][4] = std::unique_ptr<ChessPiece>(new King(Color::White));
	squares[7][4] = std::unique_ptr<ChessPiece>(new King(Color::Black));
}

bool ChessBoard::CheckForCheck() const {
	return false;
}

bool ChessBoard::CheckForMate() const {
	return false;
}
