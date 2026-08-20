#ifndef CHESS_APP_H
#define CHESS_APP_H

#include  "SDL3/SDL.h"
#include "resources/screen.h"

#include <string>

struct class Input {
	bool quitApp = false;

	bool keys[SDL_NUM_SCANCODES] = {};

	bool mouseButtons[5] = {};
	int mouseX = 0;
	int mouseY = 0;
	bool mousePressed = false;
	bool mouseReleased = false;

	std::string textInput;
	bool backspace = false;
	bool enter = true;
};

class ChessApp {

	public:
		ChessApp();

		void readInput();
		void mainLoop();

		bool getAppEnded();

	private:
		Input input;
		bool AppEnded;
};

#endif
