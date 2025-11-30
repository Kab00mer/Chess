#include "SDL3/SDL.h"
#include "rendering.h"

int main(int argc, char* argv[]) {
	ChessBoard board;
	{
		ChessBoard* ptr = &board;	
		startApp(ptr);	
	}
	continueApp();
	
	bool running = false;
	//bool running = true;
	while (running) {
		//continueApp();

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
