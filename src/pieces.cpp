#include "pieces.h"
#include <iostream>

ChessPiece::ChessPiece() : value(0) {}

bool ChessPiece::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::string ChessPiece::returnColorAndType() const {
	return "";
}

Pawn::Pawn(char c) {
	value = 1;
	color = c;
	hasMoved = false;
}

bool Pawn::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::string Pawn::returnColorAndType() const {
	return "p" + color;
}

Bishop::Bishop(char c) {
	value = 3;
	color = c;
}

bool Bishop::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::string Bishop::returnColorAndType() const {
	return color + "b";
}

Knight::Knight(char c) {
	value = 3;
	color = c;
}
bool Knight::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::string Knight::returnColorAndType() const {
	return color + "n";
}

Rook::Rook(char c) {
	value = 5;
	color = c;
	hasMoved = false;
}

bool Rook::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::string Rook::returnColorAndType() const {
	return color + "r";
}

Queen::Queen(char c) {
	value = 8;
	color = c;
}

bool Queen::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::string Queen::returnColorAndType() const {
	return color + "q"; 
}

King::King(char c) {
	value = 0;
	color = c;
	hasMoved = false;
}

bool King::canMoveTo(const size_t x, const size_t y) const {
	return false;
}

std::string King::returnColorAndType() const {
	return color + "k";
}
