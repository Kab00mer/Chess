#ifndef LOCAL_MENU_H
#define LOCAL_MENU_H

#include "../resources/screen.h"
#include "../resources/widgets.h"

class LocalMenu : public Screen {
	public:
		LocalMenu();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*, const std::map<std::string, SDL_Texture*>&) override;

	private:
		WhoGoesFirst turnOrder;
		size_t timeControl;

		Button startButton;
		Button goBackButton;
		
		Button randomFirstButton;
		Button leftFirstButton;
		Button rightFirstButton;

		Button timeButton30;
		Button timeButton15;
		Button timeButton10;
		Button timeButton5;
		Button timeButton3;
		Button timeButton1;
};

#endif

