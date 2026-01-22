#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <set>
#include <stack>
#include <string>

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
	int x, y;
	bool operator==(const Coord& other) const { return (x == other.x && y == other.y); }
	bool operator!=(const Coord& other) const { return (x != other.x || y != other.y); }
	bool operator<(const Coord& other) const { return (x != other.x) ? x < other.x : y < other.y; }
	Coord() : x(8), y(8) {}
	Coord(int paramX, int paramY) : x(paramX), y(paramY) {}
};

struct Piece {
	Color color;
	PieceType type;
	bool hasMoved;
	Piece() : color(Color::NONE), type(PieceType::NONE), hasMoved(false) {}
	Piece(Color c, PieceType t, bool h = false) : color(c), type(t), hasMoved(h) {}
	Piece& operator=(const Piece& other) {	
		if (this != &other) {
			color = other.color;
			type = other.type;
			hasMoved = other.hasMoved;
		}
		return *this;
	}
};

struct Move {
	Coord from, to;
	Piece pieceToUndo;
	bool passantOrCastle;
	bool firstTimePieceMoved;
	bool promotion;

	Move() : from(Coord()), to(Coord()), pieceToUndo(Piece()), passantOrCastle(false)
			 , firstTimePieceMoved(false), promotion(false) {}
	Move(Coord f, Coord t, Piece p, bool pasOrCas, bool firstTime, bool pro) : from(f), to(t)
		, pieceToUndo(p), passantOrCastle(pasOrCas), firstTimePieceMoved(firstTime)
		, promotion(pro) {}
};

class ChessBoard {
	public :
		ChessBoard(Color color = Color::WHITE);

		//getters and setters
		Piece getPieceAt(const Coord) const;
		std::set<Coord> getMovesForPieceAt(const Coord) const;
		std::set<std::pair<Coord, Coord>> getAllPossibleMoves() const;
		Color getUsersColor() const;
		Color getWhoseTurnIsIt() const;
		void setNextPawnPromotion(const PieceType);
		bool getIfInCheck() const;
		Move getMostRecentMove() const;
		bool getIfMated() const;
		std::pair<bool, std::string> getIfDraw() const;
		int getPointsOf(const Color) const;

		//moving
		void movePiece(const Coord, const Coord, const bool);
		void undoMove();

		//printing board
		void printBoard() const;

	private :
		//board logic
		void updateMoves(const bool);
		bool calculateInCheck();
		void updatePoints();

		//Piece logic for possible moves
		std::set<Coord> getPossibleMovesAt(const Coord, const bool);
		std::set<Coord> possiblePawnMoves(const Coord, const bool) const;
		std::set<Coord> possibleBishopMoves(const Coord) const;
		std::set<Coord> possibleKnightMoves(const Coord) const;
		std::set<Coord> possibleRookMoves(const Coord) const;
		std::set<Coord> possibleQueenMoves(const Coord) const;
		std::set<Coord> possibleKingMoves(const Coord, const bool);
		std::set<Coord> raycastLineAt(const Coord, const int x, const int y) const;

		//data memebers
		Piece grid[8][8];
		int turn;
		std::set<std::pair<Coord, Coord>> availableMoves;
		Color usersColor;
		Color whoseTurnIsIt;
		bool inCheck;
		PieceType nextPromotion;
		std::stack<Move> moveStack;
		std::stack<Coord> enPassantStack;
		int fiftyMoveRule;
		//std::set< threeFold;
		int whitesPoints;
		int blacksPoints;
};


#endif
