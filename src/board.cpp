#include "board.h"
#include <iostream>

ChessBoard::ChessBoard(bool white) {
	userIsWhite = white;
	char user, opponent;
	if (white) {
		user = 'w';
		opponent = 'b';
	} else {
		user = 'b';
		opponent  = 'w';
	}

	for (size_t i = 0; i < 8; ++i) {
		squares[1][i] = new Pawn(opponent);
		squares[6][i] = new Pawn(user);

		//collision mapping
		for (size_t j = 0; j < 8; ++j) {
			if (i < 2) {
				collisionMap[i][j] = opponent;
			} else if (i > 5) {
				collisionMap[i][j] = user;
			} else {
				collisionMap[i][j] = '0';
			}
		}
	}
			
	squares[0][0] = new Rook(opponent);
	squares[0][7] = new Rook(opponent);
	squares[7][0] = new Rook(user);
	squares[7][7] = new Rook(user);

	squares[0][1] = new Knight(opponent);
	squares[0][6] = new Knight(opponent);
	squares[7][1] = new Knight(user);
	squares[7][6] = new Knight(user);

	squares[0][2] = new Bishop(opponent);
	squares[0][5] = new Bishop(opponent);
	squares[7][2] = new Bishop(user);
	squares[7][5] = new Bishop(user);

	squares[0][3] = new Queen(opponent);
	squares[7][3] = new Queen(user);

	squares[0][4] = new King(opponent);
	squares[7][4] = new King(user);
}

ChessBoard::~ChessBoard() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (squares[i][j]);
		}
	}
}

std::pair<char, char> ChessBoard::getPieceAt(const size_t x, const size_t y) const {
	return squares[x][y] ? squares[x][y]->returnColorAndType() : std::make_pair('0', '0');
}

std::set<std::pair<int, int>> ChessBoard::getMovesForPiece(const size_t x, const size_t y) const {
	return squares[x][y] ? squares[x][y]->getPossibleMoves(collisionMap, x, y) : std::set<std::pair<int, int>>();
}

bool ChessBoard::isUserWhite() const { return userIsWhite; }

void ChessBoard::movePiece(int x1, int y1, int x2, int y2) {
	if (squares[x1][y1]) {
		//if (squares[x1][y1]->canMoveTo(x2, y2)) {
			//also do a check for check	
		//	return true;
		//}
		delete squares[x2][y2];
		squares[x2][y2] = squares[x1][y1];
		squares[x1][y1] = nullptr;

		collisionMap[x2][y2] = collisionMap[x1][y1];
		collisionMap[x1][y1] = '0';
	}
}

bool ChessBoard::checkForCheck() const {
	//will do later
	return false;
}

bool ChessBoard::checkForMate() const {
	//will do later
	return false;
}

void ChessBoard::printBoard() const {
	for (int i = 0; i < 8; ++i) {
		std::cout << "| ";
		for (int j = 0; j < 8; ++j) {
			if (squares[i][j]) {
				std::pair<char, char> piece = squares[i][j]->returnColorAndType();
				std::cout << piece.first << piece.second << " ";
			} else {
				std::cout << "00 ";
			}
		}
		std::cout << "|\n";
	}
}

void ChessBoard::printCollisionBoard() const {
	std::cout << '\n';
	for (int i = 0; i < 8; ++i) {
		std::cout << "| ";
		for (int j = 0; j < 8; ++j) {
			std::cout << collisionMap[i][j] << " ";
		}
		std::cout << "|\n";
	}
}
