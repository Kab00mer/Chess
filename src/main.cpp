#include "chess_app.h"

int main(int argc, char* argv[]) {
	ChessApp app;

	bool exit = false;
	while (!exit) {
		app.mainLoop();
		exit = app.getQuitProgram();
	}
	
	return 0;
}
