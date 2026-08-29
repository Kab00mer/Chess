#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../resources/screen.h"

class MainMenu : public Screen {
	public:
		MainMenu();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*, const std::map<std::string, SDL_Texture*>&) override;
	
	private:
		AppState pressingAndHoveringOver;
		SDL_FRect localButton;
		SDL_FRect computerButton;
		SDL_FRect onlineButton;
		SDL_FRect quitButton;

};

#endif
