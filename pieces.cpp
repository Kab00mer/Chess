#include "pieces.h"

ChessPiece::ChessPiece() : value(0), color(Color::none) {}

bool ChessPiece::canMoveTo(std::pair<std::size_t, std::size_t>) const {
	return false;
}

std::pair<PieceType, Color> ChessPiece::returnTypeAndColor() const {
	return { PieceType::null, color };
}

Pawn::Pawn(Color c) {
	value = 1;
	color = c;
	hasMoved = false;
}

bool Pawn::canMoveTo(std::pair<std::size_t, std::size_t>) const {
	return false;
}

std::pair<PieceType, Color> Pawn::returnTypeAndColor() const {
	return { PieceType::P, color };
}

Bishop::Bishop(Color c) {
	value = 3;
	color = c;
}

bool Bishop::canMoveTo(std::pair<std::size_t, std::size_t>) const {
	return false;
}

std::pair<PieceType, Color> Bishop::returnTypeAndColor() const {
	return { PieceType::B, color };
}

Knight::Knight(Color c) {
	value = 3;
	color = c;
}

bool Knight::canMoveTo(std::pair<std::size_t, std::size_t>) const {
	return false;
}

std::pair<PieceType, Color> Knight::returnTypeAndColor() const {
	return { PieceType::N, color };
}

Rook::Rook(Color c) {
	value = 5;
	color = c;
	hasMoved = false;
}

bool Rook::canMoveTo(std::pair<std::size_t, std::size_t>) const {
	return false;
}

std::pair<PieceType, Color> Rook::returnTypeAndColor() const {
	return { PieceType::R, color };
}

Queen::Queen(Color c) {
	value = 8;
	color = c;
}

bool Queen::canMoveTo(std::pair<std::size_t, std::size_t>) const {
	return false;
}

std::pair<PieceType, Color> Queen::returnTypeAndColor() const {
	return { PieceType::Q, color };
}

King::King(Color c) {
	value = 0;
	color = c;
	hasMoved = false;
}

bool King::canMoveTo(std::pair<std::size_t, std::size_t>) const {
	return false;
}

std::pair<PieceType, Color> King::returnTypeAndColor() const {
	return { PieceType::K, color };
}
