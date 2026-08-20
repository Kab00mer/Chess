#include "main_menu.h"

#include <iostream>

static const size_t WINDOW_HEIGHT = 360;
static const size_t WINDOW_WIDTH = 640;
static const size_t BUTTON_HEIGHT = 100;
static const size_t BUTTON_WIDTH = 400;
static const size_t BUTTON_PADDING_X = 100;
static const size_t BUTTON_PADDING_Y = 137;


MainMenu::MainMenu() {
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

void MainMenu::processInput(const Input& input) {
	if (SDL_PointInRectFloat(&input.mousePos, &localButton)) {
		if (input.mousePressed) {
			pressingAndHoveringOver = AppState::LOCAL_MENU;
		} else if (input.mouseReleased) {
			setNextState(AppState::LOCAL_MENU);
		}

	} else if (SDL_PointInRectFloat(&input.mousePos, &computerButton)) {
		if (input.mousePressed) {
			pressingAndHoveringOver = AppState::COMPUTER_MENU;
		} else if (input.mouseReleased) {
			setNextState(AppState::COMPUTER_MENU);
		}

	} else if (SDL_PointInRectFloat(&input.mousePos, &onlineButton)) {
		if (input.mousePressed) {
			pressingAndHoveringOver = AppState::ONLINE_MENU;
		} else if (input.mouseReleased) {	
			setNextState(AppState::ONLINE_MENU);
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &quitButton)) {
		if (input.mousePressed) {
			pressingAndHoveringOver = AppState::ONLINE_GAME;
		} else if (input.mouseReleased) {
			setUserExited(true);
		}
	} else {
		pressingAndHoveringOver = AppState::NONE;
	}
}

void MainMenu::processRender(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	SDL_RenderClear(renderer);

	pressingAndHoveringOver == AppState::LOCAL_MENU ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &localButton);

	pressingAndHoveringOver == AppState::COMPUTER_MENU ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &computerButton);

	pressingAndHoveringOver == AppState::ONLINE_MENU ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &onlineButton);

	pressingAndHoveringOver == AppState::ONLINE_GAME ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_RenderFillRect(renderer, &quitButton);

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
}
