#ifndef PIECES_H
#define PIECES_H

class ChessPiece {
	public :
		ChessPiece();
		virtual canMove();

	protected :
		int value;
		std::pair<size_t, size_t> currentPos;
};

class Pawn : public ChessPiece {
	public :
		Pawn();
		canMove() override;
	
	private :
		bool hasMoved;
		bool white;
};

class Bishop : public ChessPiece {
	public :
		Bishop();
		canMove() override;
};

class Knight : public ChessPiece {
	public :
		Knight();
		canMove() override;
};

class Rook : public ChessPiece {
	public :
		Rook();
		canMove() override;
};

class Queen : public ChessPiece {
	public :
		Queen();
		canMove() override;
};

class King : public ChessPiece {
	public :
		King();
		canMove() override;
};

#endif
