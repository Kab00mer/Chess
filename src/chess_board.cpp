#include "chess_board.h"
#include <iostream>

ChessBoard::ChessBoard(Color color = Color::WHITE) {
	whoseTurnIsIt = Color::WHITE;
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

	updateMoves();
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
	std::set<Coord> foundMoves;
	
	for (std::pair<Coord, Coord> move : availableMoves) {
		if (move.first == pos) {
			foundMoves.insert(move.second);
		}
	}

	return foundMoves;
}

Color ChessBoard::getUsersColor() const { return usersColor; }

Color ChessBoard::getWhoseTurnIsIt() const { return whoseTurnIsIt; }

void ChessBoard::updateMoves() {
	availableMoves.clear();

	//Then sees if any move would cause their king to be in check with checkForCheck()
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (grid[i][j] && grid[i][j]->color == whoseTurnIsIt) {
				std::set<Coord> results;
				Coord current = {i, j};

				switch (grid[i][j]->type) {
					case PieceType::PAWN :
						results = possiblePawnMoves(current);
						break;
					case PieceType::BISHOP :
						results = possibleBishopMoves(current);
						break;
					case PieceType::KNIGHT :
						results = possibleKnightMoves(current);
						break;
					case PieceType::ROOK :
						results = possibleRookMoves(current);
						break;
					case PieceType::QUEEN :
						results = possibleQueenMoves(current);
						break;
					case PieceType::KING :
						results = possibleKingMoves(current);
						break;
				}

				//then process results
				for (Coord c : results) {
					//std::cout << c.x << ", " << c.y << '\n';
					availableMoves.insert(std::make_pair(current, c));
				}
			}
		}
	}
}

void ChessBoard::movePiece(const Coord pos1, const Coord pos2) {
	if (grid[pos1.x][pos1.y]) {
		grid[pos1.x][pos1.y]->hasMoved = true;
		
		if (grid[pos2.x][pos2.y]) {
			delete grid[pos2.x][pos2.y];
		}
		grid[pos2.x][pos2.y] = grid[pos1.x][pos1.y];
		grid[pos1.x][pos1.y] = nullptr;

		whoseTurnIsIt = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
		updateMoves();
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

std::set<Coord> ChessBoard::possiblePawnMoves(const Coord pos) {
	std::set<Coord> moves;
	
	int offset;
	switch (grid[pos.x][pos.y]->color) {
		case Color::WHITE :
			offset = -1;
			break;
		case Color::BLACK :
			offset = 1;
			break;
	}

	if (!grid[pos.x + offset][pos.y]) {
		moves.insert( {pos.x + offset, pos.y} );
		if (!grid[pos.x][pos.y]->hasMoved && !grid[pos.x + offset * 2][pos.y]) {
			moves.insert( {pos.x + offset * 2, pos.y} );
		}
	}

	if (pos.y + 1 < 8 && (!grid[pos.x + offset][pos.y + 1] 
			|| grid[pos.x + offset][pos.y + 1]->color != grid[pos.x][pos.y]->color)) {
		moves.insert( {pos.x + offset, pos.y + 1} );
	}
	if (pos.y - 1 >= 0 && (!grid[pos.x + offset][pos.y - 1]
			|| grid[pos.x + offset][pos.y - 1]->color != grid[pos.x][pos.y]->color)) {
		moves.insert( {pos.x + offset, pos.y - 1} );
	}

	return moves;
}

std::set<Coord> ChessBoard::possibleBishopMoves(const Coord pos) {
	std::set<Coord> moves;
	
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i != 0 && j != 0) {
				for (Coord c : raycastLineAt(pos, i, j)) {
					moves.insert(c);
				}
			}
		}
	}

	return moves;
}

std::set<Coord> ChessBoard::possibleKnightMoves(const Coord pos) {
	std::set<Coord> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i != 0 && j != 0) {
				int currentX = pos.x + i;
				int currentY = pos.y + j;
				
				if (currentX >= 0 && currentX < 8 && currentY >= 0 && currentY < 8) {
					if (currentX + i >= 0 && currentX + i < 8 
							&& (!grid[currentX + i][currentY] 
							|| grid[currentX + i][currentY]->color != grid[pos.x][pos.y]->color)) {
						moves.insert( {currentX + i, currentY} );
					}
					if (currentY + j >= 0 && currentY + j < 8 
							&& (!grid[currentX][currentY + j]
							|| grid[currentX][currentY + j]->color != grid[pos.x][pos.y]->color)) {
						moves.insert( {currentX, currentY + j} );
					}
				}
			}
		}
	}

	return moves;
}

std::set<Coord> ChessBoard::possibleRookMoves(const Coord pos) {
	std::set<Coord> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if ((i == 0) != (j == 0)) {
				for (Coord c : raycastLineAt(pos, i, j)) {
					moves.insert(c);
				}
			}
		}
	}
	return moves;
}

std::set<Coord> ChessBoard::possibleQueenMoves(const Coord pos) {
	std::set<Coord> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i != 0 || j != 0) {
				for (Coord c : raycastLineAt(pos, i, j)) {
					moves.insert(c);
				}
			}
		}
	}

	return moves;
}

std::set<Coord> ChessBoard::possibleKingMoves(const Coord pos) {
	std::set<Coord> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i != 0 || j != 0) {
				int currentX = pos.x + i;
				int currentY = pos.y + j;
				if (currentX >= 0 && currentX < 8 && currentY >= 0 && currentY < 8 
						&& (!grid[currentX][currentY] 
							|| grid[currentX][currentY]->color != grid[pos.x][pos.y]->color)) {

					moves.insert( {currentX, currentY} );	
				}
			}
		}
	}

	return moves;
}

std::set<Coord> ChessBoard::raycastLineAt(const Coord pos, const int xDirect, const int yDirect) {
	std::set<Coord> result;
	int currentX = pos.x + xDirect;
	int currentY = pos.y + yDirect;

	bool collision = false;
	while (!collision) {
		if (currentX >= 0 && currentX < 8 && currentY >= 0 && currentY < 8) {
			if (!grid[currentX][currentY]) {
				result.insert( {currentX, currentY} );
				currentX += xDirect;
				currentY += yDirect;
			} else if (grid[currentX][currentY]->color == grid[pos.x][pos.y]->color) {
				collision = true;
			} else {
				result.insert( {currentX, currentY} );
				collision = true;
			}

		} else {
			collision = true;
		}
	}

	return result;
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
	std::cout << '\n';
}
