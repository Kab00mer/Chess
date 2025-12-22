#include "chess_board.h"
#include <iostream>

ChessBoard::ChessBoard(Color color = Color::WHITE) {
	usersColor = color;
	Color opponent = (usersColor == Color::WHITE) ? Color::BLACK : Color::WHITE;

	for (size_t i = 0; i < 8; ++i) {
		grid[1][i] = new Piece(opponent, PieceType::PAWN);
		grid[6][i] = new Piece(usersColor, PieceType::PAWN);
	}
			
	grid[0][0] = new Piece(opponent, PieceType::ROOK);
	grid[0][7] = new Piece(opponent, PieceType::ROOK);
	grid[7][0] = new Piece(usersColor, PieceType::ROOK);
	grid[7][7] = new Piece(usersColor, PieceType::ROOK);

	grid[0][1] = new Piece(opponent, PieceType::KNIGHT);
	grid[0][6] = new Piece(opponent, PieceType::KNIGHT);
	grid[7][1] = new Piece(usersColor, PieceType::KNIGHT);
	grid[7][6] = new Piece(usersColor, PieceType::KNIGHT);

	grid[0][2] = new Piece(opponent, PieceType::BISHOP);
	grid[0][5] = new Piece(opponent, PieceType::BISHOP);
	grid[7][2] = new Piece(usersColor, PieceType::BISHOP);
	grid[7][5] = new Piece(usersColor, PieceType::BISHOP);

	grid[0][3] = new Piece(opponent, PieceType::QUEEN);
	grid[7][3] = new Piece(usersColor, PieceType::QUEEN);

	grid[0][4] = new Piece(opponent, PieceType::KING);
	grid[7][4] = new Piece(usersColor, PieceType::KING);
}

ChessBoard::~ChessBoard() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (grid[i][j]) {
				delete grid[i][j];
			}
		}
	}
}

Piece ChessBoard::getPieceAt(const Coord pos) const {
	return grid[pos.x][pos.y] ? *grid[pos.x][pos.y] : Piece(Color::NONE, PieceType::NONE);
}

std::set<Coord> ChessBoard::getMovesForPieceAt(const Coord pos) const {
	return {};
}

Color ChessBoard::getUsersColor() const {
	return usersColor;
}

void ChessBoard::movePiece(const Coord pos1, const Coord pos2) {
	if (grid[pos1.x][pos1.y]) {
		/*
		grid[x1][y1]->pieceMoved();	
		ChessPiece* ptr = grid[x2][y2];
		
		delete grid[x2][y2];
		grid[x2][y2] = grid[x1][y1];
		grid[x1][y1] = nullptr;

		collisionMap[x2][y2] = collisionMap[x1][y1];
		collisionMap[x1][y1] = '0';

		whitesTurn = !whitesTurn;
		*/
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

std::set<Coord> possiblePawnMoves(const Coord) {
	std::set<Coord> moves;
	return moves;
}

std::set<Coord> possibleBishopMoves(const Coord) {
	std::set<Coord> moves;
	return moves;
}

std::set<Coord> possibleKnightMoves(const Coord) {
	std::set<Coord> moves;
	return moves;
}

std::set<Coord> possibleRookMoves(const Coord) {
	std::set<Coord> moves;
	return moves;
}

std::set<Coord> possibleQueenMoves(const Coord) {
	std::set<Coord> moves;
	return moves;
}

std::set<Coord> possibleKingMoves(const Coord) {
	std::set<Coord> moves;
	return moves;
}

void ChessBoard::printBoard() const {
	std::cout << '\n';
	for (int i = 0; i < 8; ++i) {
		std::cout << "| ";
		for (int j = 0; j < 8; ++j) {
			if (grid[i][j]) {
				switch (grid[i][j]->color) {
					case Color::WHITE :
						std::cout << 'w';
						break;
					case Color::BLACK :
						std::cout << 'b';
						break;
					default:
						break;
				}

				switch (grid[i][j]->type) {
					case PieceType::PAWN :
						std::cout << 'p';
						break;
					case PieceType::BISHOP :
						std::cout << 'b';
						break;
					case PieceType::KNIGHT :
						std::cout << 'n';
						break;
					case PieceType::ROOK :
						std::cout << 'r';
						break;
					case PieceType::QUEEN :
						std::cout << 'q';
						break;
					case PieceType::KING :
						std::cout << 'k';
						break;
					default:
						break;
				}

				std::cout << ' ';

			} else {
				std::cout << "00 ";
			}
		}
		std::cout << "|\n";
	}
}
