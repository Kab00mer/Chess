#include "input.h"
#include "rendering.h"
#include "SDL3/SDL.h"

bool checkInput() {
	bool quit = false;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			quit = true;	
		}
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			holdPiece();			
		} else if (event.type == SDL_EVENT_MOUSE_MOTION) {
			setCurrentMousePos(event.button.x, event.button.y);	
		} else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
			releasePiece();
		} else if (event.type == SDL_EVENT_KEY_DOWN) {
			keyPressed();
		}
	}

	return quit;
}
