#include "SDL3/SDL.h"

#include "resources/screen.h"
#include "menus/main_menu.h"
#include "menus/local_menu.h"
#include "menus/computer_menu.h"
#include "menus/online_menu.h"
#include "games/local_game.h"
#include "games/computer_game.h"
#include "games/online_game.h"

#include <unordered_map>
#include <memory>

int main(int argc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("Chess App", 1280, 720, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

	//sets SDL's Coord system to be 640 by 360 and strech depending on how big the window is
	SDL_SetREnderLogicalPresentation(renderer, 640, 360, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	AppState state = AppState::MAIN_MENU;
	std::unordered_map<AppState, std::unique_ptr<Screen>> screens;

	screens[AppState::MAIN_MENU] = std::make_unique<MainMenu>();
	screens[AppState::LOCAL_MENU] = std::make_unique<LocalMenu>();
	screens[AppState::COMPUTER_MENU] = std::make_unique<ComputerMenu>();
	screens[AppState::ONLINE_MENU] = std::make_unique<OnlineMenu>();
	screens[AppState::LOCAL_GAME] = nullptr;
	screens[AppState::COMPUTER_GAME] = nullptr;
	screens[AppState::ONLINE_GAME] = nullptr;

	bool exit = false;
	while (!exit) {
		screens[state]->processInput();
		screens[state]->processUpdate();
		screens[state]->processRender();

		exit = screens[state]->exit();
		AppState nextState = screens[state]->nextState();
		switch (nextState) {
			case AppState::NONE:
				break;

			case AppState::LOCAL_GAME:
				screens[AppState::LOCAL_GAME] = std::make_unique<LocalGame>()
				state = nextState
				break;

			case AppState::COMPUTER_GAME:
				screens[AppState::COMPUTER_GAME] = std::make_unique<ComputerGame>();
				state = nextState;
				break;

			case AppState::ONLINE_GAME:
				screens[AppState::ONLINE_GAME] = std::make_unique<OnlineGame>();
				state = nextState;
				break;

			default:
				if (state == AppState::LOCAL_GAME || state == AppState::COMPUTER_GAME
						|| state == AppState::ONLINE_GAME) {
					delete screens[state];
					screens[state] = nullptr;
				}
				state = nextState;
		}
	}

	return 0;
}
