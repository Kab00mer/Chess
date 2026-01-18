#ifndef RENDERING_H
#define RENDERING_H

#include "chess_board.h"
#include <string>

//basic app functions
void startApp(ChessBoard*);
void continueApp();
void stopApp();

//drawing
void drawHighlightAt(const int x, const int y);

//collecting mouse and piece data
std::string convertPieceToStr(const Piece);
void setCurrentMousePos(const float, const float);
Coord convertMousePosToCoord();

//gets called by input.cpp when user clicks
void holdPiece();
void releasePiece();
void keyPressed();

//applying board state
void updateBoard();

//robot
void tryToMoveBot();

#endif
