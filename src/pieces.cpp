#include "pieces.h"
#include <iostream>

//----------Chess Piece-------------
ChessPiece::ChessPiece(int v, char c, bool m) : value(v), color(c), hasMoved(m) {}

std::pair<char, char> ChessPiece::getColorAndType() const { return {}; }

std::set<std::pair<int, int>> ChessPiece::getPossibleMoves(const char (*collisions)[8], int x, int y) const 
{ return {}; }

void ChessPiece::pieceMoved() { hasMoved = true; }

bool ChessPiece::hasPieceMoved() const { return hasMoved; }

//----------Pawn-------------
Pawn::Pawn(char c) : ChessPiece(1, c, false) {}

std::pair<char, char> Pawn::getColorAndType() const { return {color, 'p'}; }

std::set<std::pair<int, int>> Pawn::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::set<std::pair<int, int>> moves;
	
	if (color == 'w') {
		//forward
		if (*(collisions[x - 1] + y) == '0') {
			moves.insert(std::make_pair(x - 1, y));
			if (!hasMoved && *(collisions[x - 2] + y) == '0') {
				moves.insert(std::make_pair(x - 2, y));
			}
		}
		
		//diagonal
		if (y + 1 < 8 && *(collisions[x - 1] + y + 1) == 'b') {
			moves.insert(std::make_pair(x - 1, y + 1));
		}
		if (y - 1 >= 0 && *(collisions[x - 1] + y - 1) == 'b') {
			moves.insert(std::make_pair(x - 1, y - 1));
		}

	} else {
		//forward
		if (*(collisions[x + 1] + y) == '0') {
			moves.insert(std::make_pair(x + 1, y));
			if (!hasMoved && *(collisions[x + 2] + y) == '0') {
				moves.insert(std::make_pair(x + 2, y));
			}
		}

		//diagonal
		if (y + 1 < 8 && *(collisions[x + 1] + y + 1) == 'w') {
			moves.insert(std::make_pair(x + 1, y + 1));
		}
		if (y - 1 >= 0 && *(collisions[x + 1] + y - 1) == 'w') {
			moves.insert(std::make_pair(x + 1, y - 1));
		}
	}
	
	return moves;
}

//----------Bishop-------------
Bishop::Bishop(char c) : ChessPiece(3, c, false) {}

std::pair<char, char> Bishop::getColorAndType() const { return {color, 'b'}; }

std::set<std::pair<int, int>> Bishop::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::set<std::pair<int, int>> moves;
	
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			//we only care about diagonals
			if (j != 0 && i != 0) {
				int tempX = x + i;
				int tempY = y + j;
				bool hitEnd = false;
				
				//keep going until there is a piece or edge
				while (!hitEnd && tempX >= 0 && tempX < 8 && tempY >= 0 && tempY < 8) {
					char piece = *(collisions[tempX] + tempY);
				
					if (piece == '0') {
						moves.insert(std::make_pair(tempX, tempY));
						tempX += i;
						tempY += j;
					} else if (piece == color) {
						hitEnd = true;	
					} else {
						moves.insert(std::make_pair(tempX, tempY));
						hitEnd = true;
					}
				}
			}
		}
	}

	return moves;
}

//----------Knight-------------
Knight::Knight(char c) : ChessPiece(3, c, false) {}

std::pair<char, char> Knight::getColorAndType() const { return {color, 'n'}; }

std::set<std::pair<int, int>> Knight::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::set<std::pair<int, int>> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			//first we get the diagonals
			if (j != 0 && i != 0) {
				int tempX = x + i;
				int tempY = y + j;

				if (tempX >= 0 && tempX < 8 && tempY >= 0 && tempY < 8) {
					//then we make the L shape by adding another i to x or j to y
					if (tempX + i >= 0 && tempX + i < 8 && *(collisions[tempX + i] + tempY) != color) {
						moves.insert(std::make_pair(tempX + i, tempY));
					}
					if (tempY + j >= 0 && tempY + j < 8 && *(collisions[tempX] + tempY + j) != color) {
						moves.insert(std::make_pair(tempX, tempY + j));
					}
				}
			}
		}
	}


	return moves;
}

//----------Rook-------------
Rook::Rook(char c) : ChessPiece(5, c, false) {}

std::pair<char, char> Rook::getColorAndType() const { return {color, 'r'}; }

std::set<std::pair<int, int>> Rook::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::set<std::pair<int, int>> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			//we only care about cardinal directions
			if ((i == 0 && j != 0) || (i != 0 && j == 0)) {
				int tempX = x + i;
				int tempY = y + j;
				bool hitEnd = false;
				
				//keep going until there is a piece or edge
				while (!hitEnd && tempX >= 0 && tempX < 8 && tempY >= 0 && tempY < 8) {
					char piece = *(collisions[tempX] + tempY);
				
					if (piece == '0') {
						moves.insert(std::make_pair(tempX, tempY));
						tempX += i;
						tempY += j;
					} else if (piece == color) {
						hitEnd = true;	
					} else {
						moves.insert(std::make_pair(tempX, tempY));
						hitEnd = true;
					}
				}
			}
		}
	}

	return moves;
}

//----------Queen-------------
Queen::Queen(char c) : ChessPiece(8, c, false) {}

std::pair<char, char> Queen::getColorAndType() const { return {color, 'q'}; }

std::set<std::pair<int, int>> Queen::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::set<std::pair<int, int>> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			//we care about all directions
			if (i != 0 || j != 0) {
				int tempX = x + i;
				int tempY = y + j;
				bool hitEnd = false;
				
				//keep going until there is a piece or edge
				while (!hitEnd && tempX >= 0 && tempX < 8 && tempY >= 0 && tempY < 8) {
					char piece = *(collisions[tempX] + tempY);
				
					if (piece == '0') {
						moves.insert(std::make_pair(tempX, tempY));
						tempX += i;
						tempY += j;
					} else if (piece == color) {
						hitEnd = true;	
					} else {
						moves.insert(std::make_pair(tempX, tempY));
						hitEnd = true;
					}
				}
			}
		}
	}

	return moves;
}

//----------King-------------
King::King(char c) : ChessPiece(0, c, false) {}

std::pair<char, char> King::getColorAndType() const { return {color, 'k'}; }

std::set<std::pair<int, int>> King::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::set<std::pair<int, int>> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {

			//we care about all directions	
			if ((i != 0 || j != 0)
				&& (x + i >= 0 && x + i < 8 && y + j >= 0 && y + j < 8)
				&& (*(collisions[x + i] + y + j) != color)) {

				moves.insert(std::make_pair(x + i, y + j));
			}
		}
	}
	
	return moves;
}
