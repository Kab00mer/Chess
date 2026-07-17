#include "chess_board.h"
#include <iostream>

static const Coord emptyCoord = {8, 8};
static const Piece emptyPiece = Piece(Color::NONE, PieceType::NONE);

ChessBoard::ChessBoard(Color color) {
	turn = 0;
	fiftyMoveRule = 0;
	whitesPoints = 0;
	blacksPoints = 0;
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
	
	updateMoves(false);
}

Piece ChessBoard::getPieceAt(const Coord pos) const { return grid[pos.x][pos.y]; }
PieceType ChessBoard::getPieceTypeAt(const Coord pos) const { return grid[pos.x][pos.y].type; }

std::set<Coord> ChessBoard::getMovesForPieceAt(const Coord pos) const {
	std::set<Coord> foundMoves;
	for (std::pair<Coord, Coord> move : availableMoves) {
		if (move.first == pos) {
			foundMoves.insert(move.second);
		}
	}
	return foundMoves;
}

std::set<std::pair<Coord, Coord>> ChessBoard::getAllPossibleMoves() const { return availableMoves; }
Color ChessBoard::getUsersColor() const { return usersColor; }
Color ChessBoard::getWhoseTurnIsIt() const { return whoseTurnIsIt; }
void ChessBoard::setNextPawnPromotion(const PieceType type) { nextPromotion = type; }
bool ChessBoard::getIfInCheck() const { return inCheck; }
Move ChessBoard::getMostRecentMove() const { return !moveStack.empty() ? moveStack.top() : Move(); }
bool ChessBoard::getIfMated() const { return (availableMoves.size() == 0 && inCheck); }

std::pair<bool, std::string> ChessBoard::getIfDraw() const { 
	if (availableMoves.size() == 0 && !inCheck) {
		return {true, "STALEMATE"};

	} else if (fiftyMoveRule >= 50) {
		return {true, "FIFTY MOVE RULE"};

	//} else if () {
		//put here threefold repetition	
	//	return {true, "THREEFOLD REPETITION"};
	} else {
		//check for insufficient material
		int knights = 0;
		int bishops = 0;
		int nonKings = 0;
		int i = 0;
		int j = 0;
		while (knights < 2 && bishops < 2 && nonKings < 1 && i < 8) {
			j = 0;
			while (knights < 2 && bishops < 2 && nonKings < 1 && j < 8) {
				switch (grid[i][j].type) {
					case PieceType::KING :
					case PieceType::NONE :
						break;
					case PieceType::KNIGHT :
						++knights;
						break;
					case PieceType::BISHOP :
						++bishops;
						break;
					default :
						++nonKings;
				}
				++j;
			}
			++i;
		}

		if (knights < 2 && bishops < 2 && nonKings < 1) {
			return {true, "INSUFFICENT MATERIAL"};
		}
	}

	return {false, ""};
}

int ChessBoard::getPointsOf(const Color c) const {
 	return c == Color::WHITE ? whitesPoints - blacksPoints : blacksPoints - whitesPoints;
}

Coord ChessBoard::getKingOf(const Color c) const {
	bool found = false;
	int i = 0;
	int j = 0;
	while (!found && i < 8) {
		j = 0;
		while (!found && j < 8) {
			(grid[i][j].type == PieceType::KING && grid[i][j].color == c) ? found = true : ++j;
		}

		if (!found) {++i;}
	}

	if (!found) {
		std::cerr << "ERROR: King was not found during a search!" << '\n';
		return {};
	} else {
		return {i, j};
	}
}

void ChessBoard::movePiece(const Coord pos1, const Coord pos2, const bool ignoreFiftyRule) {
	if (grid[pos1.x][pos1.y].type != PieceType::NONE) {
		Move currentMove;
		currentMove.from = pos1;
		currentMove.to = pos2;

		if (!grid[pos1.x][pos1.y].hasMoved) {
			grid[pos1.x][pos1.y].hasMoved = true;
			currentMove.firstTimePieceMoved = true;
		}

		currentMove.pieceToUndo = grid[pos2.x][pos2.y];	
		grid[pos2.x][pos2.y] = grid[pos1.x][pos1.y];
		grid[pos1.x][pos1.y] = emptyPiece;

		if (!ignoreFiftyRule) {
			currentMove.pieceToUndo.type == PieceType::NONE ? ++fiftyMoveRule : fiftyMoveRule = 0;
		}

		if (grid[pos2.x][pos2.y].type == PieceType::PAWN) {
			if (pos2.x == 0 || pos2.x == 7) {
				//promotion
				if (nextPromotion == PieceType::NONE) {
					std::cout << "ERROR: No piece type was set for the next pawn promotion!" << '\n';
				} else {
					currentMove.promotion = true;
					grid[pos2.x][pos2.y].type = nextPromotion;
					nextPromotion = PieceType::NONE;
				}

			} else if (!enPassantStack.empty() && pos2 == enPassantStack.top()) {
				//enPassant was executed
				currentMove.passantOrCastle = true;
				grid[pos1.x][pos2.y] = emptyPiece;
			}

			if (pos1.x - pos2.x == 2 || pos2.x - pos1.x == 2) {
				//we add to enPassantStack
				Coord enPassant((pos1.x + pos2.x) / 2, pos1.y);
				enPassantStack.push(enPassant);

			} else {
				enPassantStack.push(emptyCoord);
			}

		} else {
			enPassantStack.push(emptyCoord);
		}

		if (grid[pos2.x][pos2.y].type == PieceType::KING) {
			if (pos2.y == 6 && pos2.y - pos1.y == 2) {
				currentMove.passantOrCastle = true;
				grid[pos2.x][pos2.y - 1] = grid[pos2.x][7];
				grid[pos2.x][7] = emptyPiece;
			} else if (pos2.y == 2 && pos1.y - pos2.y == 2) {
				currentMove.passantOrCastle = true;
				grid[pos2.x][pos2.y + 1] = grid[pos2.x][0];
				grid[pos2.x][0] = emptyPiece;
			}
		}

		moveStack.push(currentMove);

		whoseTurnIsIt = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
		updateMoves(false);
		updatePoints();
		++turn;

	} else {
		std::cout << "ERROR: Tried to move a nonexistant piece" << '\n';
	}
}

void ChessBoard::undoMove() {
	if (moveStack.empty()) {
		std::cout << "ERROR: Tried to undo with no moves left" << '\n';
		return;
	}

	Move current = moveStack.top();
	moveStack.pop();
	enPassantStack.pop();

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
			grid[current.from.x][current.to.y] = Piece(whoseTurnIsIt, PieceType::PAWN, true); //it has moved
		}
		
	} else if (current.promotion) {
		nextPromotion = grid[current.from.x][current.from.y].type;
		grid[current.from.x][current.from.y].type = PieceType::PAWN;
	}

	whoseTurnIsIt = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
	updateMoves(false);
	--turn;
}

void ChessBoard::printBoard() const {
	Coord enPassant = enPassantStack.empty() ? emptyCoord : enPassantStack.top();

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

void ChessBoard::updateMoves(const bool ignoreFiftyRule) {
	inCheck = calculateInCheck();
	availableMoves.clear();

	if (!ignoreFiftyRule && inCheck) { fiftyMoveRule = 0; }

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
		while (!found && j < 8) {
			(grid[i][j].color == whoseTurnIsIt && grid[i][j].type == PieceType::KING) ? found = true : ++j;
		}
		
		if (!found) { ++i; j = 0; }
	}

	if (!found) {
		std::cout << "ERROR: King was not found when calculating for check" << '\n';
	} else {
		Coord king = {i, j};
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

void ChessBoard::updatePoints() {
	whitesPoints = 0;
	blacksPoints = 0;

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int amount = 0;
			switch(grid[i][j].type) {
				case PieceType::PAWN :
					++amount;
					break;
				case PieceType::BISHOP :
				case PieceType::KNIGHT :
					amount += 3;
					break;
				case PieceType::ROOK :
					amount += 5;
					break;
				case PieceType::QUEEN :
					amount += 9;
					break;
				default:
					break;
			}

			grid[i][j].color == Color::WHITE ? whitesPoints += amount : blacksPoints += amount;
		}
	}
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
	if (usersColor == Color::WHITE) {
		offset = grid[pos.x][pos.y].color == Color::WHITE ? -1 : 1;
	} else {
		offset = grid[pos.x][pos.y].color == Color::WHITE ? 1 : -1;
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
				Coord enPassant = enPassantStack.empty() ? emptyCoord : enPassantStack.top();
				if (grid[pos.x + offset][pos.y + i].type != PieceType::NONE 
						&& grid[pos.x + offset][pos.y + i].color != grid[pos.x][pos.y].color) {
					//normal attack
					moves.insert( {pos.x + offset, pos.y + i} );
				} else if (pos.x + offset == enPassant.x && pos.y + i == enPassant.y) {
					//enPassant
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
