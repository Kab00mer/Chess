#include "local_menu.h"

LocalMenu::LocalMenu() : Screen() {
	highlighted = Selection::NONE;
	turnOrder = Selection::RANDOM;
	timeControl = Selection::MIN_10;

	startButton.x = 200;
	startButton.y = 280;
	startButton.w = 240;
	startButton.h = 70;

	goBackButton.x = 10;
	goBackButton.y = 10;
	goBackButton.w = 150;
	goBackButton.h = 50;
	
	randomFirstButton.x = 110;
	randomFirstButton.y = 100;
	randomFirstButton.w = 150;
	randomFirstButton.h = 40;

	leftFirstButton.x = 110;
	leftFirstButton.y = 150;
	leftFirstButton.w = 270;
	leftFirstButton.h = 40;

	rightFirstButton.x = 110;
	rightFirstButton.y = 200;
	rightFirstButton.w = 270;
	rightFirstButton.h = 40;

	timeButton30.x = 450;
	timeButton30.y = 30;
	timeButton30.w = 100;
	timeButton30.h = 30;

	timeButton15.x = 450;
	timeButton15.y = 70;
	timeButton15.w = 100;
	timeButton15.h = 30;

	timeButton10.x = 450;
	timeButton10.y = 110;
	timeButton10.w = 100;
	timeButton10.h = 30;

	timeButton5.x = 450;
	timeButton5.y = 150;
	timeButton5.w = 100;
	timeButton5.h = 30;

	timeButton3.x = 450;
	timeButton3.y = 190;
	timeButton3.w = 100;
	timeButton3.h = 30;

	timeButton1.x = 450;
	timeButton1.y = 230;
	timeButton1.w = 100;
	timeButton1.h = 30;
}

void LocalMenu::processInput(const Input& input) {
	if (SDL_PointInRectFloat(&input.mousePos, &startButton)) {
		if (input.mousePressed) {
			highlighted = Selection::START;
		} else if (input.mouseReleased) {
			switch (turnOrder) {
				case Selection::RANDOM:
					setWhoFirst(WhoGoesFirst::RANDOM);
					break;
				case Selection::LEFT_FIRST:
					setWhoFirst(WhoGoesFirst::LEFT_FIRST);
					break;
				case Selection::RIGHT_FIRST:
					setWhoFirst(WhoGoesFirst::RIGHT_FIRST);
					break;
			}

			switch (timeControl) {
				case Selection::MIN_30:
					setTimeControl(30);
					break;
				case Selection::MIN_15:
					setTimeControl(15);
					break;
				case Selection::MIN_10:
					setTimeControl(10);
					break;
				case Selection::MIN_5:
					setTimeControl(5);
					break;
				case Selection::MIN_3:
					setTimeControl(3);
					break;
				case Selection::MIN_1:
					setTimeControl(1);
					break;
			}
			setNextState(AppState::LOCAL_GAME);
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &goBackButton)) {
		if (input.mousePressed) {
			highlighted = Selection::RETURN;
		} else if (input.mouseReleased) {
			setNextState(AppState::MAIN_MENU);
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &randomFirstButton)) {
		if (input.mousePressed) {
			highlighted = Selection::RANDOM;
		} else if (input.mouseReleased) {
			turnOrder = Selection::RANDOM;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &leftFirstButton)) {
		if (input.mousePressed) {
			highlighted = Selection::LEFT_FIRST;
		} else if (input.mouseReleased) {
			turnOrder = Selection::LEFT_FIRST;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &rightFirstButton)) {
		if (input.mousePressed) {
			highlighted = Selection::RIGHT_FIRST;
		} else if (input.mouseReleased) {
			turnOrder = Selection::RIGHT_FIRST;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &timeButton30)) {
		if (input.mousePressed) {
			highlighted = Selection::MIN_30;
		} else if (input.mouseReleased) {
			timeControl = Selection::MIN_30;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &timeButton15)) {
		if (input.mousePressed) {
			highlighted = Selection::MIN_15;
		} else if (input.mouseReleased) {
			timeControl = Selection::MIN_15;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &timeButton10)) {
		if (input.mousePressed) {
			highlighted = Selection::MIN_10;
		} else if (input.mouseReleased) {
			timeControl = Selection::MIN_10;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &timeButton5)) {
		if (input.mousePressed) {
			highlighted = Selection::MIN_5;
		} else if (input.mouseReleased) {
			timeControl = Selection::MIN_5;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &timeButton3)) {
		if (input.mousePressed) {
			highlighted = Selection::MIN_3;
		} else if (input.mouseReleased) {
			timeControl = Selection::MIN_3;
		}
	} else if (SDL_PointInRectFloat(&input.mousePos, &timeButton1)) {
		if (input.mousePressed) {
			highlighted = Selection::MIN_1;
		} else if (input.mouseReleased) {
			timeControl = Selection::MIN_1;
		}
	} else {
		highlighted = Selection::NONE;
	}
}

void LocalMenu::processRender(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	SDL_RenderClear(renderer);

	highlighted == Selection::START ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200);
	SDL_RenderFillRect(renderer, &startButton);

	highlighted == Selection::RETURN ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200)
		: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 200);
	SDL_RenderFillRect(renderer, &goBackButton);

	(highlighted == Selection::RANDOM || turnOrder == Selection::RANDOM) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &randomFirstButton);

	(highlighted == Selection::LEFT_FIRST || turnOrder == Selection::LEFT_FIRST) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &leftFirstButton);

	(highlighted == Selection::RIGHT_FIRST || turnOrder == Selection::RIGHT_FIRST) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &rightFirstButton);

	(highlighted == Selection::MIN_30 || timeControl == Selection::MIN_30) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &timeButton30);

	(highlighted == Selection::MIN_15 || timeControl == Selection::MIN_15) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &timeButton15);

	(highlighted == Selection::MIN_10 || timeControl == Selection::MIN_10) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &timeButton10);

	(highlighted == Selection::MIN_5 || timeControl == Selection::MIN_5) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &timeButton5);

	(highlighted == Selection::MIN_3 || timeControl == Selection::MIN_3) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &timeButton3);

	(highlighted == Selection::MIN_1 || timeControl == Selection::MIN_1) 
		? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, 150, 150, 150, 200);
	SDL_RenderFillRect(renderer, &timeButton1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_SetRenderScale(renderer, 2.0f, 2.0f);

	SDL_RenderDebugText(renderer, static_cast<int>((startButton.x + 10) / 2.0f),
			static_cast<int>((startButton.y + 10) / 2.0f), "START");

	SDL_RenderDebugText(renderer, static_cast<int>((goBackButton.x + 10) / 2.0f),
			static_cast<int>((goBackButton.y + 10) / 2.0f), "RETURN");

	SDL_RenderDebugText(renderer, static_cast<int>((randomFirstButton.x + 10) / 2.0f),
			static_cast<int>((randomFirstButton.y - 20) / 2.0f), "TURN ORDER");

	SDL_RenderDebugText(renderer, static_cast<int>((randomFirstButton.x + 10) / 2.0f),
			static_cast<int>((randomFirstButton.y + 10) / 2.0f), "Random");

	SDL_RenderDebugText(renderer, static_cast<int>((leftFirstButton.x + 10) / 2.0f),
			static_cast<int>((leftFirstButton.y + 10) / 2.0f), "Left:W/Right:B");

	SDL_RenderDebugText(renderer, static_cast<int>((rightFirstButton.x + 10) / 2.0f),
			static_cast<int>((rightFirstButton.y + 10) / 2.0f), "Left:B/Right:W");

	SDL_RenderDebugText(renderer, static_cast<int>((timeButton30.x - 30) / 2.0f),
			static_cast<int>((timeButton30.y - 20) / 2.0f), "TIME CONTROL");

	SDL_RenderDebugText(renderer, static_cast<int>((timeButton30.x + 10) / 2.0f),
			static_cast<int>((timeButton30.y + 10) / 2.0f), "30Min");

	SDL_RenderDebugText(renderer, static_cast<int>((timeButton15.x + 10) / 2.0f),
			static_cast<int>((timeButton15.y + 10) / 2.0f), "15Min");

	SDL_RenderDebugText(renderer, static_cast<int>((timeButton10.x + 10) / 2.0f),
			static_cast<int>((timeButton10.y + 10) / 2.0f), "10Min");

	SDL_RenderDebugText(renderer, static_cast<int>((timeButton5.x + 10) / 2.0f),
			static_cast<int>((timeButton5.y + 10) / 2.0f), "5Min");

	SDL_RenderDebugText(renderer, static_cast<int>((timeButton3.x + 10) / 2.0f),
			static_cast<int>((timeButton3.y + 10) / 2.0f), "3Min");

	SDL_RenderDebugText(renderer, static_cast<int>((timeButton1.x + 10) / 2.0f),
			static_cast<int>((timeButton1.y + 10) / 2.0f), "1Min");

	SDL_RenderPresent(renderer);
}
