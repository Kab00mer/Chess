#include "robots.h"
#include <set>
#include <random>
#include <ctime>
#include <stack>
#include <vector>
#include <iostream>
#include <limits>

static ChessBoard* board;

void initiateRobots(ChessBoard* newBoard) { 
	board = newBoard; 
	srand(time(NULL));
}

void randomRobot() {
	std::set<std::pair<Coord, Coord>> possibleMoves;
	board->setNextPawnPromotion(PieceType::QUEEN);

	//getting all possible moves
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			Coord from = {i, j};
			for (Coord to : board->getMovesForPieceAt(from)) {
				possibleMoves.insert(std::make_pair(from, to));
			}
		}
	}

	//rng and pulling raffled move
	int randomNumber = std::rand() % possibleMoves.size();
	auto iter = possibleMoves.begin();
	std:advance(iter, randomNumber);
	std::pair<Coord, Coord> chosen = *iter;
	board->movePiece(chosen.first, chosen.second, false);
}

void pointRobot(const int moveDepth) {
	if (moveDepth < 1) {
		std::cerr << "ERROR: Please insert a positive integer to pointRobot(int)!" << '\n';
	}

	std::set<std::pair<int, std::pair<Coord, Coord>>> movesAndPoints;
	Color robotColor = board->getWhoseTurnIsIt();
	for (std::pair<Coord, Coord> move : board->getAllPossibleMoves()) {
		//force each possible move, and calculate game trees for each
		board->movePiece(move.first, move.second, true);
		movesAndPoints.insert(std::make_pair(pointDepthFirstSearch(moveDepth * 2, 1, robotColor), move));
		board->undoMove();
	}

	//now we select the move that had the highest calculated points
	std::pair<Coord, Coord> selectedMove = movesAndPoints.begin()->second;
	int maxPoints = std::numeric_limits<int>::lowest();
	for (std::pair<int, std::pair<Coord, Coord>> move : movesAndPoints) {
		//if the points are the same, randomly pick one
		if (move.first > maxPoints || (move.first == maxPoints && std::rand() % 2 == 0)) {
			maxPoints = move.first;
			selectedMove = move.second;
		}
	}

	board->movePiece(selectedMove.first, selectedMove.second, false);
}

int pointDepthFirstSearch(const int maxDepth, const int currentDepth, const Color robotColor) {
	if (currentDepth == maxDepth) {
		return board->getPointsOf(robotColor);
	} else if (board->getIfMated()) {
		return currentDepth % 2  == 0 ? 1000 : -1000;
	}

	int maxOrMin = currentDepth % 2 == 0 ? std::numeric_limits<int>::lowest() 
		: std::numeric_limits<int>::max();

	for (std::pair<Coord, Coord> move : board->getAllPossibleMoves()) {
		board->movePiece(move.first, move.second, true);
		int val = pointDepthFirstSearch(maxDepth, currentDepth + 1, robotColor);
		board->undoMove();

		if (currentDepth % 2 == 0) {
			if (val > maxOrMin) { maxOrMin = val; }
		} else {
			if (val < maxOrMin) { maxOrMin = val; }
		}
	}

	return maxOrMin;
}
