#include "board.h"
#include "rendering.cpp"
#include "input.cpp"

int main(int argc, char* argv[]) {
	ChessBoard board();
	startApp();
	renderChessBoard(board);

	bool running = true;
	while (running) {
		running = input();
	}

	stopApp();

	return 0;
}
