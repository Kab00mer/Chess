#include "main_menu.h"

#include <iostream>

static const size_t WINDOW_WIDTH = 640;
static const size_t WINDOW_HEIGHT = 360;

static const size_t BUTTON_WIDTH = 340;
static const size_t BUTTON_HEIGHT = 70;
static const size_t BUTTON_PADDING_X = 150;
static const size_t BUTTON_PADDING_Y = 16;

static const float TEXT_SCALE = 3.0f;
static const size_t LOCAL_TEXT_OFFSET = 50;
static const size_t COMPUTER_TEXT_OFFSET = 55;
static const size_t ONLINE_TEXT_OFFSET = 35;
static const size_t QUIT_TEXT_OFFSET = 110;
static const size_t TEXT_OFFSET_Y = 23;

MainMenu::MainMenu() : Screen() {
	localButton.x = BUTTON_PADDING_X;
	localButton.y = BUTTON_PADDING_Y;
	localButton.w = BUTTON_WIDTH;
	localButton.h = BUTTON_HEIGHT;

	computerButton.x = BUTTON_PADDING_X;
	computerButton.y = BUTTON_PADDING_Y * 2 + BUTTON_HEIGHT;
	computerButton.w = BUTTON_WIDTH;
	computerButton.h = BUTTON_HEIGHT;

	onlineButton.x = BUTTON_PADDING_X;
	onlineButton.y = BUTTON_PADDING_Y * 3 + BUTTON_HEIGHT * 2;
	onlineButton.w = BUTTON_WIDTH;
	onlineButton.h = BUTTON_HEIGHT;

	quitButton.x = BUTTON_PADDING_X;
	quitButton.y = BUTTON_PADDING_Y * 4 + BUTTON_HEIGHT * 3;
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

void MainMenu::processRender(SDL_Renderer* renderer, const std::map<std::string, SDL_Texture*>& pieces) {
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
		: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
	SDL_RenderFillRect(renderer, &quitButton);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderRect(renderer, &localButton);
	SDL_RenderRect(renderer, &computerButton);
	SDL_RenderRect(renderer, &onlineButton);
	SDL_RenderRect(renderer, &quitButton);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_SetRenderScale(renderer, TEXT_SCALE, TEXT_SCALE);
	SDL_RenderDebugText(renderer, static_cast<int>((localButton.x + LOCAL_TEXT_OFFSET) / TEXT_SCALE), 
			static_cast<int>((localButton.y + TEXT_OFFSET_Y) / TEXT_SCALE), "Local Game");

	SDL_SetRenderScale(renderer, TEXT_SCALE - 0.5f, TEXT_SCALE - 0.05f);
	SDL_RenderDebugText(renderer, static_cast<int>((computerButton.x + COMPUTER_TEXT_OFFSET) / TEXT_SCALE),
			static_cast<int>((computerButton.y + TEXT_OFFSET_Y) / TEXT_SCALE), "Versus Computer");

	SDL_SetRenderScale(renderer, TEXT_SCALE, TEXT_SCALE);
	SDL_RenderDebugText(renderer, static_cast<int>((onlineButton.x + ONLINE_TEXT_OFFSET) / TEXT_SCALE),
			static_cast<int>((onlineButton.y + TEXT_OFFSET_Y) / TEXT_SCALE), "Online Game");

	SDL_RenderDebugText(renderer, static_cast<int>((quitButton.x + QUIT_TEXT_OFFSET) / TEXT_SCALE), 
			static_cast<int>((quitButton.y + TEXT_OFFSET_Y) / TEXT_SCALE), "Quit");

	SDL_RenderPresent(renderer);
}
