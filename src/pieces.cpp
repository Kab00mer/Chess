#include "pieces.h"
#include <iostream>

ChessPiece::ChessPiece() : value(0) {}

bool ChessPiece::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> ChessPiece::returnColorAndType() const {
	return {};
}

std::set<std::pair<int, int>> ChessPiece::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::cout << *collisions[0] << '\n';
	return {};	
}

Pawn::Pawn(char c) {
	value = 1;
	color = c;
	hasMoved = false;
}

bool Pawn::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> Pawn::returnColorAndType() const {
	return {color, 'p'};
}

std::set<std::pair<int, int>> Pawn::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	return {std::make_pair(x + 1, y + 1)};
}

Bishop::Bishop(char c) {
	value = 3;
	color = c;
}

bool Bishop::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> Bishop::returnColorAndType() const {
	return {color, 'b'};
}

std::set<std::pair<int, int>> Bishop::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	return {};
}

Knight::Knight(char c) {
	value = 3;
	color = c;
}
bool Knight::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> Knight::returnColorAndType() const {
	return {color, 'n'};
}

std::set<std::pair<int, int>> Knight::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	return {};
}

Rook::Rook(char c) {
	value = 5;
	color = c;
	hasMoved = false;
}

bool Rook::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> Rook::returnColorAndType() const {
	return {color, 'r'};
}

std::set<std::pair<int, int>> Rook::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	return {};
}

Queen::Queen(char c) {
	value = 8;
	color = c;
}

bool Queen::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> Queen::returnColorAndType() const {
	return {color, 'q'};
}

std::set<std::pair<int, int>> Queen::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	return {};
}

King::King(char c) {
	value = 0;
	color = c;
	hasMoved = false;
}

bool King::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> King::returnColorAndType() const {
	return {color, 'k'};
}

std::set<std::pair<int, int>> King::getPossibleMoves(const char (*collisions)[8], int x, int y) const {
	std::set<std::pair<int, int>> moves;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if ((i != 0 || j != 0)
				&& (x + i >= 0 && x + i < 8 && y + j >= 0 && y + j < 8)
				&& (*(collisions[x + i] + y + j) != color)) {

				moves.insert(std::make_pair(x + i, y + j));
			}
		}
	}
	
	for (std::pair<int, int> m : moves) {
		std::cout << "ONE POINT" << '\n';
		std::cout << m.first << " : " << m.second << '\n';
	}
	return moves;
}
