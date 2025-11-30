#ifndef PIECES_H
#define PIECES_H

#include <utility>

enum Color {
	White, 
	Black,
	none
};
enum PieceType {
	P,
	B,
	N,
	R,
	Q,
	K,
	null
};

class ChessPiece {
	public :
		ChessPiece();
		virtual bool canMoveTo(std::pair<std::size_t, std::size_t>) const;
		virtual std::pair<PieceType, Color> returnTypeAndColor() const;

	protected :
		int value;
		Color color;
};

class Pawn : public ChessPiece {
	public :
		Pawn(Color);
		bool canMoveTo(std::pair<std::size_t, std::size_t>) const override;
		std::pair<PieceType, Color> returnTypeAndColor() const override;
	
	private :
		bool hasMoved;
};

class Bishop : public ChessPiece {
	public :
		Bishop(Color);
		bool canMoveTo(std::pair<std::size_t, std::size_t>) const override;
		std::pair<PieceType, Color> returnTypeAndColor() const override;
};

class Knight : public ChessPiece {
	public :
		Knight(Color);
		bool canMoveTo(std::pair<std::size_t, std::size_t>) const override;
		std::pair<PieceType, Color> returnTypeAndColor() const override;
};

class Rook : public ChessPiece {
	public :
		Rook(Color);
		bool canMoveTo(std::pair<std::size_t, std::size_t>) const override;
		std::pair<PieceType, Color> returnTypeAndColor() const override;
	
	private :
		bool hasMoved;
};

class Queen : public ChessPiece {
	public :
		Queen(Color);
		bool canMoveTo(std::pair<std::size_t, std::size_t>) const override;
		std::pair<PieceType, Color> returnTypeAndColor() const override;
};

class King : public ChessPiece {
	public :
		King(Color);
		bool canMoveTo(std::pair<std::size_t, std::size_t>) const override;
		std::pair<PieceType, Color> returnTypeAndColor() const override;
	
	private :
		bool hasMoved;	
};

#endif
