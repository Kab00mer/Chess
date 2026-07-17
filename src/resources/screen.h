#ifndef SCREEN_H
#define SCREEN_H

#include "SDL3/SDL.h"

#include <string>

enum class AppState {
	NONE,
	LOCAL_MENU,
	COMPUTER_MENU,
	ONLINE_MENU,
	LOCAL_GAME,
	COMPUTER_GAME,
	ONLINE_GAME
};

class Window {
	public:
		virtual void processInput() {}
		virtual void processUpdate() {}
		virtual void processRender(SDL_Renderer*) {}

		virtual bool exit() { return false; }
		virtual AppState nextState() { return AppState::NONE; }
};

#endif
