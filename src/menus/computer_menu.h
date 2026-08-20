#ifndef COMPUTER_MENU_H
#define COMPUTER_MENU_H

#include "../resources/screen.h"

class ComputerMenu : public Screen {
	public:
		ComputerMenu();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*) override;

	private:

};

#endif
