#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <set>

enum class Color {
	WHITE,
	BLACK,
	NONE
};

enum class PieceType {
	PAWN,
	BISHOP,
	KNIGHT,
	ROOK,
	QUEEN,
	KING,
	NONE
};

struct Coord {
	int x;
	int y;
	bool operator==(const Coord& other) const { return (x == other.x && y == other.y); }
	bool operator!=(const Coord& other) const { return (x != other.x || y != other.y); }
	bool operator<(const Coord& other) const { return (x != other.x) ? x < other.x : y < other.y; }
	Coord() : x(8), y(8) {}
	Coord(int paramX, int paramY) : x(paramX), y(paramY) {}
};

struct Piece {
	Color color;
	PieceType type;
	bool hasMoved = false;
	Piece() : color(Color::NONE), type(PieceType::NONE) {}
	Piece(Color c, PieceType t) : color(c), type(t) {}
};

class ChessBoard {
	public :
		ChessBoard(Color color);
		~ChessBoard();

		//getters and setters
		Piece getPieceAt(const Coord) const;
		std::set<Coord> getMovesForPieceAt(const Coord) const;
		Color getUsersColor() const;
		Color getWhoseTurnIsIt() const;
		void setNextPawnPromotion(const PieceType);
		bool getIfInCheck() const;
		bool getIfMated() const;
		bool getIfStalemated() const;

		//moving
		void movePiece(const Coord, const Coord);

		//printing board
		void printBoard() const;

	private :
		//board logic
		void updateMoves();
		bool calculateInCheck();

		//Piece logic for possible moves
		std::set<Coord> getPossibleMovesAt(const Coord);
		std::set<Coord> possiblePawnMoves(const Coord) const;
		std::set<Coord> possibleBishopMoves(const Coord) const;
		std::set<Coord> possibleKnightMoves(const Coord) const;
		std::set<Coord> possibleRookMoves(const Coord) const;
		std::set<Coord> possibleQueenMoves(const Coord) const;
		std::set<Coord> possibleKingMoves(const Coord);
		std::set<Coord> raycastLineAt(const Coord, const int x, const int y) const;

		//data memebers
		Piece* grid[8][8];
		std::set<std::pair<Coord, Coord>> availableMoves;
		Color usersColor;
		Color whoseTurnIsIt;
		Coord enPassant;
		bool inCheck;
		PieceType nextPromotion;
};

#endif
