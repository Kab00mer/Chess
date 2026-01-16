#include "robots.h"
#include <set>
#include <random>
#include <ctime>

static ChessBoard* board;

void initiateRobots(ChessBoard* newBoard) {

	board = newBoard;
}

void randomRobot() {
	std::set<std::pair<Coord, Coord>> possibleMoves;
	board->setNextPawnPromotion(PieceType::QUEEN);

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Coord from = {i, j};
			for (Coord to : board->getMovesForPieceAt(from)) {
				possibleMoves.insert(std::make_pair(from, to));
			}
		}
	}


	srand(time(NULL));
	int randomNumber = std::rand() % possibleMoves.size();
	auto iter = possibleMoves.begin();
	std:advance(iter, randomNumber);
	std::pair<Coord, Coord> chosen = *iter;
	board->movePiece(chosen.first, chosen.second);
}
