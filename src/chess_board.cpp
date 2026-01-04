#include "chess_board.h"
#include <iostream>

static const Coord emptyCoord = {8, 8};
static const Piece emptyPiece = Piece(Color::NONE, PieceType::NONE);

ChessBoard::ChessBoard(Color color) {
	turn = 0;
	whoseTurnIsIt = Color::WHITE;
	usersColor = color;
	nextPromotion = PieceType::NONE;
	
	Color opponent = (usersColor == Color::WHITE) ? Color::BLACK : Color::WHITE;

	for (size_t i = 0; i < 8; ++i) {
		for (int j = 2; j < 6; ++j) {
			grid[j][i] = emptyPiece;
		}

		grid[1][i] = Piece(opponent, PieceType::PAWN);
		grid[6][i] = Piece(usersColor, PieceType::PAWN);
	}
			
	grid[0][0] = Piece(opponent, PieceType::ROOK);
	grid[0][7] = Piece(opponent, PieceType::ROOK);
	grid[7][0] = Piece(usersColor, PieceType::ROOK);
	grid[7][7] = Piece(usersColor, PieceType::ROOK);

	grid[0][1] = Piece(opponent, PieceType::KNIGHT);
	grid[0][6] = Piece(opponent, PieceType::KNIGHT);
	grid[7][1] = Piece(usersColor, PieceType::KNIGHT);
	grid[7][6] = Piece(usersColor, PieceType::KNIGHT);

	grid[0][2] = Piece(opponent, PieceType::BISHOP);
	grid[0][5] = Piece(opponent, PieceType::BISHOP);
	grid[7][2] = Piece(usersColor, PieceType::BISHOP);
	grid[7][5] = Piece(usersColor, PieceType::BISHOP);

	grid[0][3] = Piece(opponent, PieceType::QUEEN);
	grid[7][3] = Piece(usersColor, PieceType::QUEEN);

	grid[0][4] = Piece(opponent, PieceType::KING);
	grid[7][4] = Piece(usersColor, PieceType::KING);
	
	updateMoves();
}

Piece ChessBoard::getPieceAt(const Coord pos) const { return grid[pos.x][pos.y]; }

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
	if (grid[pos1.x][pos1.y].type != PieceType::NONE) {
		Move current;

		grid[pos1.x][pos1.y].hasMoved = true;
		
		grid[pos2.x][pos2.y] = grid[pos1.x][pos1.y];
		grid[pos1.x][pos1.y] = emptyPiece;

		if (grid[pos2.x][pos2.y].type == PieceType::PAWN) {
			if (pos2.x == 0 || pos2.x == 7) {
				if (nextPromotion == PieceType::NONE) {
					std::cout << "ERROR: No piece type was set for the next pawn promotion!" << '\n';
				} else {
					grid[pos2.x][pos2.y].type = nextPromotion;
					nextPromotion = PieceType::NONE;
				}
				enPassant = emptyCoord;

			} else if (enPassant.x != 8 && pos2 == enPassant) {
				grid[pos1.x][pos2.y] = emptyPiece;
			} else if (pos2.x - pos1.x == 2) {
				enPassant = Coord(pos1.x + 1, pos1.y);
			} else if (pos2.x - pos1.x == -2) {
				enPassant = Coord(pos1.x - 1, pos1.y);
			} else {
				enPassant = emptyCoord;
			}

		} else {
			enPassant = emptyCoord;
		}

		if (grid[pos2.x][pos2.y].type == PieceType::KING) {
			if (pos2.y == 6 && pos2.y - pos1.y == 2) {
				grid[pos2.x][pos2.y - 1] = grid[pos2.x][7];
				grid[pos2.x][7] = emptyPiece;
			} else if (pos2.y == 2 && pos1.y - pos2.y == 2) {
				grid[pos2.x][pos2.y + 1] = grid[pos2.x][0];
				grid[pos2.x][0] = emptyPiece;
			}
		}

		whoseTurnIsIt = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
		updateMoves();
		++turn;

	} else {
		std::cout << "ERROR: Tried to move a nonexistant piece" << '\n';
	}
}

void ChessBoard::undoMove() {
	Move current = moveStack.top();
	moveStack.pop();

	grid[current.from.x][current.from.y] = grid[current.to.x][current.to.y];
	grid[current.to.x][current.to.y] = current.pieceToUndo;

	grid[current.from.x][current.from.y].hasMoved = !current.firstTimePieceMoved;

	if (current.passantOrCastle) {
		if (grid[current.from.x][current.from.y].type == PieceType::KING) {
			//undo castling
			if (current.to.y == 6) {
				grid[current.from.x][7] = grid[current.from.x][5];
				grid[current.from.x][5] = emptyPiece;
			} else {
				grid[current.from.x][0] = grid[current.from.x][3];
				grid[current.from.x][3] = emptyPiece;
			}
		} else {
			//undo enPassant
			Color c = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
			grid[current.from.x][current.to.y] = Piece(c, PieceType::PAWN, true); //it has moved
		}
		
	}

	whoseTurnIsIt = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
	updateMoves();
	--turn;
}

void ChessBoard::printBoard() const {
	std::cout << '\n' << "=============" << " Turn " << turn << " =============" << '\n';
	for (int i = 0; i < 8; ++i) {
		std::cout << "| ";
		for (int j = 0; j < 8; ++j) {
			switch (grid[i][j].color) {
				case Color::WHITE :
					std::cout << 'w';
					break;
				case Color::BLACK :
					std::cout << 'b';
					break;
				case Color::NONE :
					std::cout << '\'';
			}

			switch (grid[i][j].type) {
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
				case PieceType::NONE :
					std::cout << '\'';
			}

			std::cout << " ";
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
			if (grid[i][j].type != PieceType::NONE && grid[i][j].color == whoseTurnIsIt) {
				Coord current = {i, j};
				for (Coord c : getPossibleMovesAt(current, false)) { //we want all moves including attack moves
					Piece temp = grid[c.x][c.y]; 
					grid[c.x][c.y] = grid[current.x][current.y];
					grid[current.x][current.y] = emptyPiece;
					
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
			if (grid[i][j].color == whoseTurnIsIt && grid[i][j].type == PieceType::KING) {
				found = true;
			} else { 
				++j;
			}
		}
		
		if (!found) { ++i; }
	}

	Coord king = {i, j};
	if (king.x == 8) {
		std::cout << "ERROR: King was not found when calculating for check" << '\n';
	} else {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (grid[i][j].type != PieceType::NONE && grid[i][j].color != whoseTurnIsIt) {
					Coord current = {i, j};
					for (Coord c : getPossibleMovesAt(current, true)) { //we only want attack moves
						if (c == king) {
							return true;
						}
					}
				}
			}
		}
	}
	
	return false;
}

std::set<Coord> ChessBoard::getPossibleMovesAt(const Coord pos, const bool onlyAttackMoves) {
	std::set<Coord> results;
	switch (grid[pos.x][pos.y].type) {
		case PieceType::PAWN :
			//std::cout << "PAWN" << '\n';
			results = possiblePawnMoves(pos, onlyAttackMoves);
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
			results = possibleKingMoves(pos, onlyAttackMoves);
			break;
	}
	//std::cout << "FINISHED GETTING" << '\n';
	return results;
}

std::set<Coord> ChessBoard::possiblePawnMoves(const Coord pos, const bool onlyAttackMoves) const {
	std::set<Coord> moves;

	int offset;
	switch (grid[pos.x][pos.y].color) {
		case Color::WHITE :
			offset = -1;
			break;
		case Color::BLACK :
			offset = 1;
			break;
	}

	if (pos.x + offset >= 0 && pos.x + offset < 8) {
		//pawn forwards
		if (!onlyAttackMoves && grid[pos.x + offset][pos.y].type == PieceType::NONE) {
			moves.insert( {pos.x + offset, pos.y} );
			if (!grid[pos.x][pos.y].hasMoved && pos.x + offset * 2 >= 0
					&& pos.x + offset * 2 < 8 && grid[pos.x + offset * 2][pos.y].type == PieceType::NONE) {
				moves.insert( {pos.x + offset * 2, pos.y} );
			}
		}

		//pawn diagonals
		for (int i = -1; i <= 1; i += 2) {
			if (pos.y + i >= 0 && pos.y + i < 8) {
				if (grid[pos.x + offset][pos.y + i].type != PieceType::NONE 
						&& grid[pos.x + offset][pos.y + i].color != grid[pos.x][pos.y].color) {
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
							&& (grid[currentX + i][currentY].type == PieceType::NONE
							|| grid[currentX + i][currentY].color != grid[pos.x][pos.y].color)) {
						moves.insert( {currentX + i, currentY} );
					}
					if (currentY + j >= 0 && currentY + j < 8 
							&& (grid[currentX][currentY + j].type == PieceType::NONE
							|| grid[currentX][currentY + j].color != grid[pos.x][pos.y].color)) {
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

std::set<Coord> ChessBoard::possibleKingMoves(const Coord pos, const bool onlyAttackMoves) {
	std::set<Coord> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			//go in all 8 directions
			if (i != 0 || j != 0) {
				int currentX = pos.x + i;
				int currentY = pos.y + j;
				if (currentX >= 0 && currentX < 8 && currentY >= 0 && currentY < 8 
						&& (grid[currentX][currentY].type == PieceType::NONE
							|| grid[currentX][currentY].color != grid[pos.x][pos.y].color)) {
					moves.insert( {currentX, currentY} );
				}
			}
		}
	}

	if (!onlyAttackMoves) {
		//kingside castling
		if (!grid[pos.x][pos.y].hasMoved && !grid[pos.x][7].hasMoved && !inCheck 
				&& pos.y + 1 < 8 && grid[pos.x][pos.y + 1].type == PieceType::NONE 
				&& pos.y + 2 < 8 && grid[pos.x][pos.y + 2].type == PieceType::NONE
				&& grid[pos.x][7].type == PieceType::ROOK) {

				Piece king = grid[pos.x][pos.y];

				grid[pos.x][pos.y + 1] = king;
				grid[pos.x][pos.y] = emptyPiece;

				if (!calculateInCheck()) {
					moves.insert(Coord(pos.x, pos.y + 2));
				} 
	
				grid[pos.x][pos.y] = king;
				grid[pos.x][pos.y + 1] = emptyPiece;
		} 

		//queenside castling
		if (!grid[pos.x][pos.y].hasMoved && !grid[pos.x][0].hasMoved && !inCheck 
				&& pos.y - 1 >= 0 && grid[pos.x][pos.y - 1].type == PieceType::NONE 
				&& pos.y - 2 >= 0 && grid[pos.x][pos.y - 2].type == PieceType::NONE 
				&& pos.y - 3 >= 0 && grid[pos.x][pos.y - 3].type == PieceType::NONE
				&& grid[pos.x][0].type == PieceType::ROOK) {

			Piece king = grid[pos.x][pos.y];

			grid[pos.x][pos.y - 1] = king;
			grid[pos.x][pos.y] = emptyPiece;

			if (!calculateInCheck()) {

				grid[pos.x][pos.y - 2] = king;
				grid[pos.x][pos.y - 1] = emptyPiece;

				if (!calculateInCheck()) {
					moves.insert(Coord(pos.x, pos.y - 2));
				} 

				grid[pos.x][pos.y] = king;
				grid[pos.x][pos.y - 2] = emptyPiece;
	
			} else {
				grid[pos.x][pos.y] = king;
				grid[pos.x][pos.y - 1] = emptyPiece;
			}
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
			if (grid[currentX][currentY].type == PieceType::NONE) {
				result.insert( {currentX, currentY} );
				currentX += xDirect;
				currentY += yDirect;

			} else if (grid[currentX][currentY].color == grid[pos.x][pos.y].color) {
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
