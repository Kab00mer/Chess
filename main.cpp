#include "board.h"
#include "renering.cpp"

int main(int argc, char* argv[]) {
	ChessBoard board();
	createRendering();
	bool running = true;

	while (running) {
		bool quit = renderBoard();	
		quit ? running = false; :
	}

	destructRendering();

	return 0;
}
