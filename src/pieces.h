#ifndef PIECES_H
#define PIECES_H

#include <utility>
#include <string>

/*
enum Color {
	White = 'w',
	Black = 'b'
};
*/

class ChessPiece {
	public :
		ChessPiece();
		virtual bool canMoveTo(const size_t, const size_t) const;
		virtual std::string returnColorAndType() const;

	protected :
		int value;
		char color;
};

class Pawn : public ChessPiece {
	public :
		Pawn(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::string returnColorAndType() const override;
	
	private :
		bool hasMoved;
};

class Bishop : public ChessPiece {
	public :
		Bishop(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::string returnColorAndType() const override;
};

class Knight : public ChessPiece {
	public :
		Knight(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::string returnColorAndType() const override;
};

class Rook : public ChessPiece {
	public :
		Rook(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::string returnColorAndType() const override;
	
	private :
		bool hasMoved;
};

class Queen : public ChessPiece {
	public :
		Queen(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::string returnColorAndType() const override;
};

class King : public ChessPiece {
	public :
		King(char);
		bool canMoveTo(const size_t, const size_t) const override;
		std::string returnColorAndType() const override;
	
	private :
		bool hasMoved;	
};

#endif
