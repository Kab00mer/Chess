#ifndef SCREEN_H
#define SCREEN_H

#include "SDL3/SDL.h"

#include <string>
#include <map>

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

enum class WhoGoesFirst {
	RANDOM,
	LEFT_FIRST,
	RIGHT_FIRST
};

class Screen {
	public:
		Screen() : userExited(false), nextState(AppState::NONE), 
			whoFirst(WhoGoesFirst::RANDOM), timeControl(0) {}

		virtual void processInput(const Input&) {}
		virtual void processRender(SDL_Renderer*, const std::map<std::string, SDL_Texture*>&) {}

		bool getUserExited() { return userExited; }
		AppState getNextState() { return nextState; }

		void setUserExited(bool newBool) { userExited = newBool; }
		void setNextState(AppState newState) { nextState = newState; }

		WhoGoesFirst getWhoFirst() { return whoFirst; }
		void setWhoFirst(WhoGoesFirst newFirst) { whoFirst = newFirst; }

		size_t getTimeControl() { return timeControl; }
		void setTimeControl(size_t newTime) { timeControl = newTime; }

		void renderCheckeredBoard(SDL_FRect board[][8], SDL_Renderer* renderer) {
			for (size_t i = 0; i < 8; ++i) {
				for (size_t j = 0; j < 8; ++j) {
					(i + j) % 2 == 1 ? SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200) 
						: SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200);
					SDL_RenderFillRect(renderer, &board[i][j]);
				}
			}
		}

	private:
		bool userExited;
		AppState nextState;
		WhoGoesFirst whoFirst;
		size_t timeControl;
};

#endif
