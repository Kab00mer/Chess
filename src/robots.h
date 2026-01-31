#ifndef ROBOTS_H
#define ROBOTS_H

#include "chess_board.h"

void initiateRobots(ChessBoard*);
void randomRobot();
void pointRobot(const int);
int pointDepthFirstSearch(const int, const int, const Color);

#endif
