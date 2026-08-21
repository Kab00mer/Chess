#ifndef SCREEN_H
#define SCREEN_H

#include "SDL3/SDL.h"

#include <string>

enum class AppState {
	NONE,
	MAIN_MENU,
	LOCAL_MENU,
	COMPUTER_MENU,
	ONLINE_MENU,
	LOCAL_GAME,
	COMPUTER_GAME,
	ONLINE_GAME
};

struct Input {
	//bool keys[SDL_NUM_SCANCODES];		

	std::string textInput;
	bool backspace = false;
	bool enter = false;

	bool mousePressed = false;
	bool mouseReleased = false;
	SDL_FPoint mousePos;
};

class Screen {
	public:
		Screen() : userExited(false), nextState(AppState::NONE) {}

		virtual void processInput(const Input&) {}
		virtual void processRender(SDL_Renderer*) {}

		bool getUserExited() { return userExited; }
		AppState getNextState() { return nextState; }

		void setUserExited(bool newBool) { userExited = newBool; }
		void setNextState(AppState newState) { nextState = newState; }

	private:
		bool userExited;
		AppState nextState;
};

#endif
