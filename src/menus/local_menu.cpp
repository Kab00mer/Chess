#include "local_menu.h"

static const float TEXT_SCALE = 2.0f;

LocalMenu::LocalMenu() : Screen(),
	startButton(200, 280, 240, 70, "Start"),
	goBackButton(10, 10, 150, 50, "Back"),
	randomFirstButton(110, 100, 150, 40, "Random"),
	leftFirstButton(110, 150, 270, 40, "L:W | R:B"),
	rightFirstButton(110, 200, 270, 40, "L:B | R:W"),
	timeButton30(450, 30, 100, 30, "30"),
	timeButton15(450, 70, 100, 30, "15"),
	timeButton10(450, 110, 100, 30, "10"),
	timeButton5(450, 150, 100, 30, "5"),
	timeButton3(450, 190, 100, 30, "3"),
	timeButton1(450, 230, 100, 30, "1") {

	turnOrder = WhoGoesFirst::RANDOM;
	timeControl = 10;
}

void LocalMenu::processInput(const Input& input) {
	startButton.input(input);
	goBackButton.input(input);
	randomFirstButton.input(input);
	leftFirstButton.input(input);
	rightFirstButton.input(input);
	timeButton30.input(input);
	timeButton15.input(input);
	timeButton10.input(input);
	timeButton5.input(input);
	timeButton3.input(input);
	timeButton1.input(input);

	if (startButton.wasPressed) {
		switch (turnOrder) {
			case WhoGoesFirst::RANDOM:
				setWhoFirst(WhoGoesFirst::RANDOM);
				break;
			case WhoGoesFirst::LEFT_FIRST:
				setWhoFirst(WhoGoesFirst::LEFT_FIRST);
				break;
			case WhoGoesFirst::RIGHT_FIRST:
				setWhoFirst(WhoGoesFirst::RIGHT_FIRST);
				break;
		}

		setTimeControl(timeControl);
		setNextState(AppState::LOCAL_GAME);

	} else if (goBackButton.wasPressed) {
		setNextState(AppState::MAIN_MENU);

	} else if (randomFirstButton.wasPressed) {
		turnOrder = WhoGoesFirst::RANDOM;

	} else if (leftFirstButton.wasPressed) {
		turnOrder = WhoGoesFirst::LEFT_FIRST;

	} else if (rightFirstButton.wasPressed) {
		turnOrder = WhoGoesFirst::RIGHT_FIRST;

	} else if (timeButton30.wasPressed) {
		timeControl = 30;

	} else if (timeButton15.wasPressed) {
		timeControl = 15;

	} else if (timeButton10.wasPressed) {
		timeControl = 10;

	} else if (timeButton5.wasPressed) {
		timeControl = 5;

	} else if (timeButton3.wasPressed) {
		timeControl = 3;

	} else if (timeButton1.wasPressed) {
		timeControl = 1;
	}
}

void LocalMenu::processRender(SDL_Renderer* renderer, const std::map<std::string, SDL_Texture*>& pieces) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_RenderClear(renderer);

	startButton.renderWithText(renderer, TEXT_SCALE, 0, 255, 0);
	goBackButton.renderWithText(renderer, TEXT_SCALE, 255, 0, 0);

	turnOrder == WhoGoesFirst::RANDOM ? randomFirstButton.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
 		: randomFirstButton.renderWithText(renderer, TEXT_SCALE);
	turnOrder == WhoGoesFirst::LEFT_FIRST ? leftFirstButton.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: leftFirstButton.renderWithText(renderer, TEXT_SCALE);
	turnOrder == WhoGoesFirst::RIGHT_FIRST ? rightFirstButton.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: rightFirstButton.renderWithText(renderer, TEXT_SCALE);

	timeControl == 30 ? timeButton30.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: timeButton30.renderWithText(renderer, TEXT_SCALE);
	timeControl == 15 ? timeButton15.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: timeButton15.renderWithText(renderer, TEXT_SCALE);
	timeControl == 10 ? timeButton10.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: timeButton10.renderWithText(renderer, TEXT_SCALE);
	timeControl == 5 ? timeButton5.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: timeButton5.renderWithText(renderer, TEXT_SCALE);
	timeControl == 3 ? timeButton3.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: timeButton3.renderWithText(renderer, TEXT_SCALE);
	timeControl == 1 ? timeButton1.renderWithText(renderer, TEXT_SCALE, 255, 255, 255)
		: timeButton1.renderWithText(renderer, TEXT_SCALE);

	SDL_SetRenderScale(renderer, 2.0f, 2.0f);
	SDL_RenderDebugText(renderer, static_cast<int>((randomFirstButton.area.x - 10) / 2.0f),
			static_cast<int>((randomFirstButton.area.y - 20) / 2.0f), "TURN ORDER");
	SDL_RenderDebugText(renderer, static_cast<int>((timeButton30.area.x - 30) / 2.0f),
			static_cast<int>((timeButton30.area.y - 20) / 2.0f), "TIME CONTROL");

	SDL_RenderPresent(renderer);
}
