#include "main_menu.h"
#include "game_window.h"

#include <memory>
#include <iostream>

int main(int argc, char* argv[]) {
	std::unique_ptr<GameWindow> currentGame = nullptr;
//	std::unique_ptr<MainMenu> mainMenu = std::make_unique<MainMenu>();
	currentGame = std::make_unique<GameWindow>();

	/*
	bool running = true;
	while (running) {
		if (currentGame) {
			currentGame->readInput();
			currentGame->run();

			if (currentGame->didUserQuit()) {
				mainMenu = std::make_unique<MainMenu>();
				currentGame = nullptr;
			}

		} else {
			mainMenu->readInput();
			mainMenu->run();

			running = !mainMenu->didUserQuit();

			GameType selectedGame = mainMenu->userSelectedGame();
			switch (selectedGame) {
				case GameType::Local:
					currentGame = std::make_unique<GameWindow>();
					mainMenu = nullptr;
					break;
				case GameType::Computer:
					//currentGame = std::make_unique<LocalGame>();
					//mainMenu = nullptr;
					break;
				case GameType::Online:
					//currentGame = std::make_unique<LocalGame>();
					//mainMenu = nullptr;
					break;
			}
		}
	}
	*/

	return 0;
}
