#include "chess_board.h"
#include <iostream>

static const Coord emptyCoord = {8, 8};

ChessBoard::ChessBoard(Color color = Color::WHITE) {
	whoseTurnIsIt = Color::WHITE;
	usersColor = color;
	enPassant = emptyCoord;
	nextPromotion = PieceType::NONE;

	Color opponent = (usersColor == Color::WHITE) ? Color::BLACK : Color::WHITE;

	//temporary stuff
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			grid[i][j] = nullptr;
		}
	}

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
void ChessBoard::setNextPawnPromotion(const PieceType type) { nextPromotion = type; }
bool ChessBoard::getIfInCheck() const { return inCheck; }
bool ChessBoard::getIfMated() const { return (availableMoves.size() == 0 && inCheck); }
bool ChessBoard::getIfStalemated() const { return (availableMoves.size() == 0 && !inCheck); }

void ChessBoard::movePiece(const Coord pos1, const Coord pos2) {
	if (grid[pos1.x][pos1.y]) {
		grid[pos1.x][pos1.y]->hasMoved = true;
		
		if (grid[pos2.x][pos2.y]) {
			delete grid[pos2.x][pos2.y];
		}

		grid[pos2.x][pos2.y] = grid[pos1.x][pos1.y];
		grid[pos1.x][pos1.y] = nullptr;

		if (grid[pos2.x][pos2.y]->type == PieceType::PAWN) {
			if (pos2.x == 0 || pos2.x == 7) {
				if (grid[pos2.x][pos2.y]->type == PieceType::NONE) {
					std::cout << "ERROR: No piece type was set for the next pawn promotion!" << '\n';
				} else {
					grid[pos2.x][pos2.y]->type = nextPromotion;
					nextPromotion = PieceType::NONE;
				}
				enPassant = emptyCoord;

			} else if (enPassant.x != 8 && pos2 == enPassant) {
				delete grid[pos1.x][pos2.y];
				grid[pos1.x][pos2.y] = nullptr;
			} else if (pos2.x - pos1.x == 2) {
				enPassant = {pos1.x + 1, pos1.y};
			} else if (pos2.x - pos1.x == -2) {
				enPassant = {pos1.x - 1, pos1.y};
			} else {
				enPassant = emptyCoord;
			}

		} else {
			enPassant = emptyCoord;
		}

		if (grid[pos2.x][pos2.y]->type == PieceType::KING) {
			if (pos2.y == 6 && pos2.y - pos1.y == 2) {
				grid[pos2.x][pos2.y - 1] = grid[pos2.x][7];
				grid[pos2.x][7] = nullptr;
			} else if (pos2.y == 2 && pos1.y - pos2.y == 2) {
				grid[pos2.x][pos2.y + 1] = grid[pos2.x][0];
				grid[pos2.x][0] = nullptr;
			}
		}

		whoseTurnIsIt = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
		updateMoves();

	} else {
		std::cout << "ERROR: Tried to move a nonexistant piece" << '\n';
	}
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
				std::cout << " ";

			} else {
				std::cout << "00 ";
			}
		}
		std::cout << "|\n";
	}
	std::cout << '\n';
}

void ChessBoard::updateMoves() {
	inCheck = calculateInCheck();
	availableMoves.clear();

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (grid[i][j] && grid[i][j]->color == whoseTurnIsIt) {
				Coord current = {i, j};
				std::set<Coord> results = getPossibleMovesAt(current);

				for (Coord c : results) {
					Piece* temp = nullptr;
					if (grid[c.x][c.y]) {
						temp = grid[c.x][c.y];
					}
					
					grid[c.x][c.y] = grid[current.x][current.y];
					grid[current.x][current.y] = nullptr;
					
					if (!calculateInCheck()) {
						availableMoves.insert(std::make_pair(current, c));
					}

					grid[current.x][current.y] = grid[c.x][c.y];

					grid[c.x][c.y] = temp;
				}
			}
		}
	}
}

bool ChessBoard::calculateInCheck() {
	bool found = false;
	int i = 0;
	int j = 0;
	while (!found && i < 8) {
		j = 0;
		while (!found && j < 8) {
			if (grid[i][j] && grid[i][j]->color == whoseTurnIsIt && grid[i][j]->type == PieceType::KING) {
				found = true;
			} else { 
				++j;
			}
		}
		
		if (!found) { ++i; }
	}

	Coord king = {i, j};
	if (king == emptyCoord) {
		std::cout << "ERROR: King was not found when calculating for check" << '\n';
	} else {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				Coord current = {i, j};
				for (Coord c : getPossibleMovesAt(current)) {
					if (c == king) {
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

std::set<Coord> ChessBoard::getPossibleMovesAt(const Coord pos) {
	std::set<Coord> results;
	if (grid[pos.x][pos.y]) {
		switch (grid[pos.x][pos.y]->type) {
			case PieceType::PAWN :
				//std::cout << "PAWN" << '\n';
				results = possiblePawnMoves(pos);
				break;
			case PieceType::BISHOP :
				//std::cout << "BISHOP" << '\n';
				results = possibleBishopMoves(pos);
				break;
			case PieceType::KNIGHT :
				//std::cout << "KNIGHT" << '\n';
				results = possibleKnightMoves(pos);
				break;
			case PieceType::ROOK :
				//std::cout << "ROOK" << '\n';
				results = possibleRookMoves(pos);
				break;
			case PieceType::QUEEN :
				//std::cout << "QUEEN" << '\n';
				results = possibleQueenMoves(pos);
				break;
			case PieceType::KING :
				//std::cout << "KING" << '\n';
				results = possibleKingMoves(pos);
				break;
		}
	}
	//std::cout << "FINISHED GETTING" << '\n';
	return results;
}

std::set<Coord> ChessBoard::possiblePawnMoves(const Coord pos) const {
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

	if (pos.x + offset >= 0 && pos.x + offset < 8) {
		//pawn forwards
		if (!grid[pos.x + offset][pos.y]) {
			moves.insert( {pos.x + offset, pos.y} );
			if (!grid[pos.x][pos.y]->hasMoved && pos.x + offset * 2 >= 0
					&& pos.x + offset * 2 < 8 && !grid[pos.x + offset * 2][pos.y]) {
				moves.insert( {pos.x + offset * 2, pos.y} );
			}
		}

		//pawn diagonals
		for (int i = -1; i <= 1; i += 2) {
			if (pos.y + i >= 0 && pos.y + i < 8) {
				if (grid[pos.x + offset][pos.y + i] 
						&& grid[pos.x + offset][pos.y + i]->color != grid[pos.x][pos.y]->color) {
					moves.insert( {pos.x + offset, pos.y + i} );
					//std::cout << "DAIGONLA PAWN!!!" << '\n';
				} else if (pos.x + offset == enPassant.x && pos.y + i == enPassant.y) {
					//std::cout << "EN PASSANT!!!" << '\n';
					moves.insert( {pos.x + offset, pos.y + i} );
				}
			}
		}
	}

	return moves;
}

std::set<Coord> ChessBoard::possibleBishopMoves(const Coord pos) const {
	std::set<Coord> moves;
	
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			//go in all diagonal directions
			if (i != 0 && j != 0) {
				for (Coord c : raycastLineAt(pos, i, j)) {
					moves.insert(c);
				}
			}
		}
	}

	return moves;
}

std::set<Coord> ChessBoard::possibleKnightMoves(const Coord pos) const {
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

std::set<Coord> ChessBoard::possibleRookMoves(const Coord pos) const {
	std::set<Coord> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			//go in all cardinal directions
			if ((i == 0) != (j == 0)) {
				for (Coord c : raycastLineAt(pos, i, j)) {
					moves.insert(c);
				}
			}
		}
	}
	return moves;
}

std::set<Coord> ChessBoard::possibleQueenMoves(const Coord pos) const {
	std::set<Coord> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			//go in all 8 directions
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
			//go in all 8 directions
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

	//kingside castling
	if (!grid[pos.x][pos.y]->hasMoved && grid[pos.x][7] && !grid[pos.x][7]->hasMoved && !inCheck 
			&& !grid[pos.x][pos.y + 1] && !grid[pos.x][pos.y + 2]) {
			grid[pos.x][pos.y + 1] = grid[pos.x][pos.y];
			grid[pos.x][pos.y] = nullptr;
			if (!calculateInCheck()) {
				moves.insert(Coord(pos.x, pos.y + 2));
			} 
			grid[pos.x][pos.y] = grid[pos.x][pos.y + 1];
			grid[pos.x][pos.y + 1] = nullptr;
	} 

	//queenside castling
	if (!grid[pos.x][pos.y]->hasMoved && grid[pos.x][0] && !grid[pos.x][0]->hasMoved && !inCheck 
			&& !grid[pos.x][pos.y - 1] && !grid[pos.x][pos.y - 2] && !grid[pos.x][pos.y - 3]) {
		grid[pos.x][pos.y - 1] = grid[pos.x][pos.y];
		grid[pos.x][pos.y] = nullptr;
		if (!calculateInCheck()) {
			grid[pos.x][pos.y - 2] = grid[pos.x][pos.y - 1];
			grid[pos.x][pos.y - 1] = nullptr;
			if (!calculateInCheck()) {
				moves.insert(Coord(pos.x, pos.y - 2));
			} 
			grid[pos.x][pos.y] = grid[pos.x][pos.y - 2];
			grid[pos.x][pos.y - 2] = nullptr;
		} else {
			grid[pos.x][pos.y] = grid[pos.x][pos.y - 1];
			grid[pos.x][pos.y - 1] = nullptr;
		}
	}

	return moves;
}

std::set<Coord> ChessBoard::raycastLineAt(const Coord pos, const int xDirect, const int yDirect) const {
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
