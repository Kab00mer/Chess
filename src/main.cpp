#include "input.cpp"

int main(int argc, char* argv[]) {
	ChessBoard* ptr = new ChessBoard();	
	startApp(ptr);	

	ptr->printBoard();
	ptr->printCollisionBoard();
	
	bool running = true;
	while (running) {
		continueApp();
		running = !checkInput();
	}

	stopApp();
	return 0;
}
