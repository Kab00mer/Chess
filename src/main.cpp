#include "board.h"
#include "rendering.cpp"

int main(int argc, char* argv[]) {
	ChessBoard board;
	startApp();

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
	}

	stopApp();
	return 0;
}
