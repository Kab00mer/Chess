#include "pieces.h"

ChessPiece::ChessPiece() : value(0) {}

bool ChessPiece::canMoveTo(std::pair<std::size_t, std::size_t>) {
	return false;
}

Pawn::Pawn(Color c) {
	value = 1;
	color = c;
	hasMoved = false;
}

bool Pawn::canMoveTo(std::pair<std::size_t, std::size_t>) {
	return false;
}

Bishop::Bishop(Color c) {
	value = 3;
	color = c;
}

bool Bishop::canMoveTo(std::pair<std::size_t, std::size_t>) {
	return false;
}

Knight::Knight(Color c) {
	value = 3;
	color = c;
}

bool Knight::canMoveTo(std::pair<std::size_t, std::size_t>) {
	return false;
}

Rook::Rook(Color c) {
	value = 5;
	color = c;
	hasMoved = false;
}

bool Rook::canMoveTo(std::pair<std::size_t, std::size_t>) {
	return false;
}

Queen::Queen(Color c) {
	value = 8;
	color = c;
}

bool Queen::canMoveTo(std::pair<std::size_t, std::size_t>) {
	return false;
}

King::King(Color c) {
	value = 0;
	color = c;
	hasMoved = false;
}

bool King::canMoveTo(std::pair<std::size_t, std::size_t>) {
	return false;
}
