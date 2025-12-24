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

		//board logic
		void updateMoves();
		void movePiece(const Coord, const Coord);
		bool checkForCheck() const;
		bool checkForMate() const;

		//Piece logic for possible moves
		std::set<Coord> possiblePawnMoves(const Coord);
		std::set<Coord> possibleBishopMoves(const Coord);
		std::set<Coord> possibleKnightMoves(const Coord);
		std::set<Coord> possibleRookMoves(const Coord);
		std::set<Coord> possibleQueenMoves(const Coord);
		std::set<Coord> possibleKingMoves(const Coord);
		std::set<Coord> raycastLineAt(const Coord, const int x, const int y);

		//printing board
		void printBoard() const;
		void printCollisionBoard() const;

	private :
		Piece* grid[8][8];
		std::set<std::pair<Coord, Coord>> availableMoves;
		Color usersColor;
		Color whoseTurnIsIt;
		Coord enPassant;
		Coord kingsideCastle;
		Coord queensideCastle;
		bool inCheck;
};

#endif
