#include "pieces.h"
#include <iostream>

ChessPiece::ChessPiece() : value(0) {}

bool ChessPiece::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::pair<char, char> ChessPiece::returnColorAndType() const {
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
