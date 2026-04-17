#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "SDL3/SDL.h"
#include "chess_board.h"

#include <string>
#include <map>

class GameWindow {
	public:
		GameWindow();
		virtual ~GameWindow();

		void gameLoop();
		bool didUserQuit() const;

	protected:
		/*
		void renderBoardAt();
		virtual Coord convertMousePosToCoord() const;
		std::string convertPieceToCoord() const;

		void setCurrentMousePos(const float , const float);
		virtual void mousePressed();
		virtual void mouseReleased();
		*/
	
	private:
		ChessBoard* board;
		SDL_Window* window;
		SDL_Renderer* renderer;
		std::map<std::string, SDL_Texture*> textures;

		Coord selectedSquare;
		float mouseX;
		float mouseY;
		bool gameFinished;
		size_t windowWidth = 850;
		size_t windowHeight = 850;
		bool userQuit;

};

#endif
