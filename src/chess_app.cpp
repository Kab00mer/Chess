#include "chess_app.h"
#include "menus/main_menu.h"
#include "menus/local_menu.h"
#include "menus/computer_menu.h"
#include "menus/online_menu.h"
#include "games/local_game.h"
#include "games/computer_game.h"
#include "games/online_game.h"

ChessApp::ChessApp() {
	quitProgram = false;

	window.reset(SDL_CreateWindow("Chess App", 1280, 720, SDL_WINDOW_RESIZABLE));
	renderer.reset(SDL_CreateRenderer(window.get(), nullptr));

	//sets SDL's Coord system to be 640 by 360 and strech depending on how big the window is
	SDL_SetRenderLogicalPresentation(renderer.get(), 640, 360, SDL_LOGICAL_PRESENTATION_LETTERBOX);

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
	switch (nextState) {
		case AppState::NONE:
			break;

		case AppState::LOCAL_GAME:
			screens[AppState::LOCAL_GAME] = std::make_unique<LocalGame>();
			state = nextState;
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

			case SDL_EVENT_KEY_DOWN:
				break;

			case SDL_EVENT_KEY_UP:
				break;

			case SDL_EVENT_TEXT_INPUT:
				input.textInput += event.text.text;
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				input.mousePressed = true;
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP:
				input.mouseReleased = true;
				break;
		}
	}

	input.mousePos = { event.button.x, event.button.y };
}
