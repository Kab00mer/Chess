#ifndef ONLINE_MENU_H
#define ONLINE_MENU_H

#include "../resources/screen.h"

class OnlineMenu : public Screen {
	public:
		OnlineMenu();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*) override;
	
	private:
};

#endif
