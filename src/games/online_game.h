#ifndef ONLINE_GAME_H
#define ONLINE_GAME_H

#include "../resources/screen.h"
#include "../resources/chess_board.h"

class OnlineGame : public Screen {
	public:
		OnlineGame();

		void processInput(const Input&) override;
		void processRender(SDL_Renderer*, const std::map<std::string, SDL_Texture*>&) override;

	private:
		
};

#endif
