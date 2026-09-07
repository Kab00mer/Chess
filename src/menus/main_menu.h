#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../resources/screen.h"
#include "../resources/widgets.h"

class MainMenu : public Screen {
	public:
		MainMenu();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*, const std::map<std::string, SDL_Texture*>&) override;
	
	private:
		Button localButton;
		Button computerButton;
		Button onlineButton;
		Button quitButton;
};

#endif
