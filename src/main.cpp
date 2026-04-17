#include "chess_board.h"
#include "main_menu.h"
#include "game_window.h"

#include <memory>

int main(int argc, char* argv[]) {
	//normally set GameWindow to nullptr at the start
	std::unique_ptr<GameWindow> currentGame = std::make_unique<GameWindow>();
	std::unique_ptr<MainMenu> mainMenu = nullptr;//new MainMenu();

	bool running = true;
	while (running) {
		if (currentGame) {
			currentGame->gameLoop();
		}
		
		if (mainMenu) {
		GameType selectedGame = mainMenu->userSelectedGame();
			switch (selectedGame) {
				case GameType::Local:
					//currentGame = std::make_unique<LocalGame>();
					mainMenu = nullptr;
					break;
				case GameType::Computer:
					//currentGame = std::make_unique<LocalGame>();
					mainMenu = nullptr;
					break;
				case GameType::Online:
					//currentGame = std::make_unique<LocalGame>();
					mainMenu = nullptr;
					break;
			}
		}

		if (currentGame && currentGame->didUserQuit()) {
			mainMenu = std::make_unique<MainMenu>();
			currentGame = nullptr;
		}
	}

	return 0;
}
