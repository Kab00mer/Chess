#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../resources/screen.h"

class MainMenu : public Screen {
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
