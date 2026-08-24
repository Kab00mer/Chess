#include "chess_app.h"
#include "menus/main_menu.h"
#include "menus/local_menu.h"
#include "menus/computer_menu.h"
#include "menus/online_menu.h"
#include "games/local_game.h"
#include "games/computer_game.h"
#include "games/online_game.h"

#include <iostream>

static const size_t STRETCHED_WINDOW_WIDTH = 1280;
static const size_t TRUE_WINDOW_WIDTH = 640;
static const size_t STRETCHED_WINDOW_HEIGHT = 720;
static const size_t TRUE_WINDOW_HEIGHT = 360;

static const float WINDOW_SCALE_X = static_cast<float>(TRUE_WINDOW_WIDTH) / STRETCHED_WINDOW_WIDTH;
static const float WINDOW_SCALE_Y = static_cast<float>(TRUE_WINDOW_HEIGHT) / STRETCHED_WINDOW_HEIGHT;

ChessApp::ChessApp() {
	quitProgram = false;

	window.reset(SDL_CreateWindow("Chess App", STRETCHED_WINDOW_WIDTH, STRETCHED_WINDOW_HEIGHT, 
			SDL_WINDOW_RESIZABLE));
	renderer.reset(SDL_CreateRenderer(window.get(), nullptr));

	//sets SDL's Coord system to be 640 by 360 and strech depending on how big the window is
	SDL_SetRenderLogicalPresentation(renderer.get(), TRUE_WINDOW_WIDTH, 
			TRUE_WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	screens[AppState::MAIN_MENU] = std::make_unique<MainMenu>();
	screens[AppState::LOCAL_MENU] = std::make_unique<LocalMenu>();
	screens[AppState::COMPUTER_MENU] = std::make_unique<ComputerMenu>();
	screens[AppState::ONLINE_MENU] = std::make_unique<OnlineMenu>();
	screens[AppState::LOCAL_GAME] = nullptr;
	screens[AppState::COMPUTER_GAME] = nullptr;
	screens[AppState::ONLINE_GAME] = nullptr;

	state = AppState::MAIN_MENU;
}

void ChessApp::mainLoop() {
	readInput();
		
	screens[state]->processInput(input);
	screens[state]->processRender(renderer.get());

	if (screens[state]->getUserExited()) {
		quitProgram = true;
		return;
	}

	AppState nextState = screens[state]->getNextState();
	if (nextState != AppState::NONE) {
		screens[state]->setNextState(AppState::NONE);
	}
	switch (nextState) {
		case AppState::NONE:
			break;

		case AppState::LOCAL_GAME:
			//fix later by writing unique getters for each type of menu/game
			screens[AppState::LOCAL_GAME] = std::make_unique<LocalGame>();
			screens[AppState::LOCAL_GAME]->setWhoFirst(screens[AppState::LOCAL_MENU]->getWhoFirst());
			screens[AppState::LOCAL_GAME]->setTimeControl(screens[AppState::LOCAL_MENU]->getTimeControl());
			state = nextState;
			break;

		case AppState::COMPUTER_GAME:
			//fix later by writing unique getters for each type of menu/game
			screens[AppState::COMPUTER_GAME] = std::make_unique<ComputerGame>();
			screens[AppState::COMPUTER_GAME]->setWhoFirst(screens[AppState::COMPUTER_MENU]->getWhoFirst());
			state = nextState;
			break;

		case AppState::ONLINE_GAME:
			//fix later by writing unique getters for each type of menu/game
			screens[AppState::ONLINE_GAME] = std::make_unique<OnlineGame>();
			screens[AppState::ONLINE_GAME]->setTimeControl(screens[AppState::ONLINE_MENU]->getTimeControl());
			state = nextState;
			break;

		default:
			if (state == AppState::LOCAL_GAME || state == AppState::COMPUTER_GAME
					|| state == AppState::ONLINE_GAME) {
				screens[state].reset();
			}
			state = nextState;
	}
}

bool ChessApp::getQuitProgram() { return quitProgram; }

void ChessApp::readInput() {
	input.textInput.clear();
	input.backspace = false;
	input.enter = false;
	input.mousePressed = false;
	input.mouseReleased = false;

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
				quitProgram = true;
				break;

			case SDL_EVENT_TEXT_INPUT:
				input.textInput += event.text.text;
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				input.mousePos = { event.button.x * WINDOW_SCALE_X, event.button.y * WINDOW_SCALE_Y};
				input.mousePressed = true;
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP:
				input.mousePos = { event.button.x * WINDOW_SCALE_X, event.button.y * WINDOW_SCALE_Y};
				input.mouseReleased = true;
				break;
		}
	}
}
