#ifndef LOCAL_MENU_H
#define LOCAL_MENU_H

#include "../resources/screen.h"

class LocalMenu : public Screen {
	public:
		LocalMenu();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*) override;

	private:
		enum class Selection {
			NONE,
			START,
			RETURN,
			RANDOM,
			LEFT_FIRST,
			RIGHT_FIRST,
			MIN_30,
			MIN_15,
			MIN_10,
			MIN_5,
			MIN_3,
			MIN_1
		};

		Selection highlighted;
		Selection turnOrder;
		Selection timeControl;

		SDL_FRect startButton;
		SDL_FRect goBackButton;
		
		SDL_FRect randomFirstButton;
		SDL_FRect leftFirstButton;
		SDL_FRect rightFirstButton;

		SDL_FRect timeButton30;
		SDL_FRect timeButton15;
		SDL_FRect timeButton10;
		SDL_FRect timeButton5;
		SDL_FRect timeButton3;
		SDL_FRect timeButton1;
};

#endif

