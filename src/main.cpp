#include "chess_board.h"
#include "rendering.h"
#include "input.h"


int main(int argc, char* argv[]) {
	ChessBoard* ptr = new ChessBoard(Color::WHITE);	
	startApp(ptr);	
	
	bool running = true;
	while (running) {
		continueApp();
		running = !checkInput();
	}

	stopApp();
	return 0;
}
