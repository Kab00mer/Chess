#include "main_menu.h"

#include <iostream>

static const size_t WINDOW_HEIGHT = 600;
static const size_t WINDOW_WIDTH = 600;
static const size_t BUTTON_HEIGHT = 100;
static const size_t BUTTON_WIDTH = 400;
static const size_t BUTTON_PADDING_X = 100;
static const size_t BUTTON_PADDING_Y = 137;


MainMenu::MainMenu() : Window("ChessMenu", WINDOW_WIDTH, WINDOW_HEIGHT) {
	currentSelection = GameType::None;

	localButton.x = BUTTON_PADDING_X;
	localButton.y = BUTTON_PADDING_Y - 100;
	localButton.w = BUTTON_WIDTH;
	localButton.h = BUTTON_HEIGHT;

	computerButton.x = BUTTON_PADDING_X;
	computerButton.y = BUTTON_PADDING_Y * 2 - 100;
	computerButton.w = BUTTON_WIDTH;
	computerButton.h = BUTTON_HEIGHT;

	onlineButton.x = BUTTON_PADDING_X;
	onlineButton.y = BUTTON_PADDING_Y * 3 - 100;
	onlineButton.w = BUTTON_WIDTH;
	onlineButton.h = BUTTON_HEIGHT;

	quitButton.x = BUTTON_PADDING_X;
	quitButton.y = BUTTON_PADDING_Y * 4 - 100;
	quitButton.w = BUTTON_WIDTH;
	quitButton.h = BUTTON_HEIGHT;
}

void MainMenu::run() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	SDL_RenderClear(renderer);

	SDL_FPoint point = {mouseX, mouseY};

	(SDL_PointInRectFloat(&point, &localButton) && mousePressed)
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &localButton);

	(SDL_PointInRectFloat(&point, &computerButton) && mousePressed)
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &computerButton);

	(SDL_PointInRectFloat(&point, &onlineButton) && mousePressed)
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &onlineButton);

	(SDL_PointInRectFloat(&point, &quitButton) && mousePressed)
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
	SDL_RenderFillRect(renderer, &quitButton);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderRect(renderer, &localButton);
	SDL_RenderRect(renderer, &computerButton);
	SDL_RenderRect(renderer, &onlineButton);
	SDL_RenderRect(renderer, &quitButton);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0,  200);
	SDL_SetRenderScale(renderer, 4.0f, 4.0f);
	SDL_RenderDebugText(renderer, localButton.x - 64, localButton.y - 18, "Local Game");

	SDL_SetRenderScale(renderer, 3.0f, 3.0f);
	SDL_RenderDebugText(renderer, computerButton.x - 59, computerButton.y - 103, "Versus Computer");

	SDL_SetRenderScale(renderer, 4.0f, 4.0f);
	SDL_RenderDebugText(renderer, onlineButton.x - 68, onlineButton.y - 224, "Online Game");
	SDL_RenderDebugText(renderer, quitButton.x - 42, quitButton.y - 327, "Quit");

	SDL_RenderPresent(renderer);

	if (SDL_PointInRectFloat(&point, &localButton) && mouseReleased) {
		currentSelection = GameType::Local;

	} else if (SDL_PointInRectFloat(&point, &computerButton) && mouseReleased) {
		currentSelection = GameType::Computer;

	} else if (SDL_PointInRectFloat(&point, &onlineButton) && mouseReleased) {
		currentSelection = GameType::Online;

	} else if (SDL_PointInRectFloat(&point, &quitButton) && mouseReleased) {
		userQuit = true;
	}
}

GameType MainMenu::userSelectedGame() {
	return currentSelection;
}
