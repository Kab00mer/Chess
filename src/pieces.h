#ifndef PIECES_H
#define PIECES_H

#include <utility>
#include <string>
#include <set>

class ChessPiece {
	public :
		virtual std::pair<char, char> getColorAndType() const;
		virtual std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const;
		void pieceMoved();
		bool hasPieceMoved() const;

	protected :
		ChessPiece(int, char, bool);

		int value;
		char color;
		bool hasMoved;
};

class Pawn : public ChessPiece {
	public :
		Pawn(char);
		std::pair<char, char> getColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class Bishop : public ChessPiece {
	public :
		Bishop(char);
		std::pair<char, char> getColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class Knight : public ChessPiece {
	public :
		Knight(char);
		std::pair<char, char> getColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class Rook : public ChessPiece {
	public :
		Rook(char);
		std::pair<char, char> getColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class Queen : public ChessPiece {
	public :
		Queen(char);
		std::pair<char, char> getColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class King : public ChessPiece {
	public :
		King(char);
		std::pair<char, char> getColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

#endif
