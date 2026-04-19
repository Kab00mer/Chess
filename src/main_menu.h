#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "window.h"

enum class GameType {
	None,
	Local,
	Computer,
	Online
};

class MainMenu : public Window {
	public:
		MainMenu();

		void run() override;
		GameType userSelectedGame();
	
	private:
		GameType currentSelection;
		SDL_FRect localButton;
		SDL_FRect computerButton;
		SDL_FRect onlineButton;
		SDL_FRect quitButton;
};

#endif
