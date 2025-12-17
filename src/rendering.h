#include "board.h"
#include "SDL3/SDL.h"

void startApp(ChessBoard*);
void continueApp();
void stopApp();
void renderPieceAt(char, char, int, int);

void setCurrentMousePos(const SDL_FPoint&);
void selectPiece();
void releasePiece();
