#ifndef MAIN_MENU_H
#define MAIN_MENU_H

enum class GameType {
	None,
	Local,
	Computer,
	Online
};

class MainMenu {
	public:
		MainMenu();
		GameType userSelectedGame();
	
	private:
};

#endif
