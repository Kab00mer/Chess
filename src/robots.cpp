#include "robots.h"
#include <set>
#include <random>
#include <ctime>
#include <queue>
#include <vector>
#include <iostream>

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

void pointRobot() {
	std::queue<std::vector<std::pair<Coord, Coord>>> queuedMoves;	
	int maxDepth = 1;

	//getting all initial possible moves
	for (std::pair<Coord, Coord> move : board->getAllPossibleMoves()) {
		std::vector<std::pair<Coord, Coord>> initialMove = {move};
		queuedMoves.push(initialMove);
	}

	std::pair<Coord, Coord> selectedMove = queuedMoves.front()[0];

	while (!queuedMoves.empty()) {
		std::vector<std::pair<Coord, Coord>> currentBranch = queuedMoves.front();
		queuedMoves.pop();
		std::cout << "(" << currentBranch[0].first.x << ", " << currentBranch[0].first.y << ") (" 
			<< currentBranch[0].second.x << ", " << currentBranch[0].second.y << ")\n";
	}

	Color robotColor = board->getWhoseTurnIsIt();
	int maxPoints = board->getPointsOf(robotColor);
	
	while (!queuedMoves.empty()) { 
		std::vector<std::pair<Coord, Coord>> currentBranch = queuedMoves.front();
		queuedMoves.pop();
		size_t moveDepth = currentBranch.size();

		//go down move tree
		for (int i = 0; i < moveDepth; ++i) {
			board->movePiece(currentBranch[i].first, currentBranch[i].second, true);
		}
		
		//add all of it's childen to queue if it hasn't reached maxDepth
		if (moveDepth < maxDepth) {
			for (std::pair<Coord, Coord> move : board->getAllPossibleMoves()) {
				currentBranch.push_back(move);
				queuedMoves.push(currentBranch);
			}
		}

		//check if the current branch is our new maximum

		//revert back to tree root
		for (int i = 0; i < moveDepth; ++i) {
			board->undoMove();
		}
	}

	board->movePiece(selectedMove.first, selectedMove.second, false);
}
