#include "board.h"
#include "SDL3/SDL.h"

void startApp(ChessBoard*);
void continueApp();
void stopApp();
void renderPieceAtCoord(char, char, int, int);
void renderPieceAtMouse(char, char);

void setCurrentMousePos(const float, const float);
std::pair<int, int> convertMousePosToCoords();
void selectPiece();
void releasePiece();
