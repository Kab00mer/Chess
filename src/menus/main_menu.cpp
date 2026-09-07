#include "main_menu.h"

#include <iostream>

static const size_t WINDOW_WIDTH = 640;
static const size_t WINDOW_HEIGHT = 360;

static const size_t BUTTON_WIDTH = 340;
static const size_t BUTTON_HEIGHT = 70;
static const size_t BUTTON_PADDING_X = 150;
static const size_t BUTTON_PADDING_Y = 16;

static const float TEXT_SCALE = 3.0f;

static const std::string LOCAL_TEXT = "Local Game";
static const std::string COMPUTER_TEXT= "Computer Game";
static const std::string ONLINE_TEXT = "Online Game";
static const std::string QUIT_TEXT = "QUIT";

MainMenu::MainMenu() : Screen(), 
	localButton(BUTTON_PADDING_X, BUTTON_PADDING_Y, BUTTON_WIDTH, BUTTON_HEIGHT, LOCAL_TEXT),
	computerButton(BUTTON_PADDING_X, BUTTON_PADDING_Y * 2 + BUTTON_HEIGHT,
			BUTTON_WIDTH, BUTTON_HEIGHT, COMPUTER_TEXT),
	onlineButton(BUTTON_PADDING_X, BUTTON_PADDING_Y * 3 + BUTTON_HEIGHT * 2,
			BUTTON_WIDTH, BUTTON_HEIGHT, ONLINE_TEXT),
	quitButton(BUTTON_PADDING_X, BUTTON_PADDING_Y * 4 + BUTTON_HEIGHT * 3,
			BUTTON_WIDTH, BUTTON_HEIGHT, QUIT_TEXT) {}

void MainMenu::processInput(const Input& input) {
	localButton.input(input);
	if (localButton.wasPressed) {
		setNextState(AppState::LOCAL_MENU);
	}

	computerButton.input(input);
	if (computerButton.wasPressed) {
		setNextState(AppState::COMPUTER_MENU);
	}

	onlineButton.input(input);
	if (onlineButton.wasPressed) {	
		setNextState(AppState::ONLINE_MENU);
	}

	quitButton.input(input);
	if (quitButton.wasPressed) {
		setUserExited(true);
	}
}

void MainMenu::processRender(SDL_Renderer* renderer, const std::map<std::string, SDL_Texture*>& pieces) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	SDL_RenderClear(renderer);

	localButton.renderWithText(renderer, TEXT_SCALE);
	computerButton.renderWithText(renderer, TEXT_SCALE);
	onlineButton.renderWithText(renderer, TEXT_SCALE);
	quitButton.renderWithText(renderer, TEXT_SCALE, 255, 0, 0);

	SDL_RenderPresent(renderer);
}
