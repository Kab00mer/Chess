#ifndef COMPUTER_GAME_H
#define COMPUTER_GAME_H

#include "../resources/screen.h"
#include "../resources/chess_board.h"

class ComputerGame : public Screen {
	public:
		ComputerGame();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*, const std::map<std::string, SDL_Texture*>&) override;

	private:

};

#endif
