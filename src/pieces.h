#ifndef PIECES_H
#define PIECES_H

#include <utility>
#include <string>
#include <set>

class ChessPiece {
	public :
		ChessPiece();
		virtual bool canMoveTo(const size_t, const size_t) const;
		virtual std::pair<char, char> returnColorAndType() const;
		virtual std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const;

	protected :
		int value;
		char color;
};

class Pawn : public ChessPiece {
	public :
		Pawn(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::pair<char, char> returnColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
	
	private :
		bool hasMoved;
};

class Bishop : public ChessPiece {
	public :
		Bishop(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::pair<char, char> returnColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class Knight : public ChessPiece {
	public :
		Knight(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::pair<char, char> returnColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class Rook : public ChessPiece {
	public :
		Rook(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::pair<char, char> returnColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
	
	private :
		bool hasMoved;
};

class Queen : public ChessPiece {
	public :
		Queen(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::pair<char, char> returnColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
};

class King : public ChessPiece {
	public :
		King(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::pair<char, char> returnColorAndType() const override;
		std::set<std::pair<int, int>> getPossibleMoves(const char (*)[8], int, int) const override;
	
	private :
		bool hasMoved;	
};

#endif
