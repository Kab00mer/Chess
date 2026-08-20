#ifndef LOCAL_MENU_H
#define LOCAL_MENU_H

#include "../resources/screen.h"

class LocalMenu : public Screen {
	public:
		LocalMenu();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*) override;

	private:
		
};

#endif

