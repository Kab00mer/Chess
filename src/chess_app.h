#ifndef CHESS_APP_H
#define CHESS_APP_H

#include "resources/screen.h"

#include <unordered_map>
#include <memory>
#include <random>

struct WindowDeleter {
	void operator()(SDL_Window* window) const {
		if (window) {
			SDL_DestroyWindow(window);
		}
	}
};

struct RendererDeleter {
	void operator()(SDL_Renderer* renderer) const {
		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
	}
};

class ChessApp {
	public:
		ChessApp();
		~ChessApp();
			
		void mainLoop();

		bool getQuitProgram();
		
	private:
		void readInput();
		
		std::unique_ptr<SDL_Window, WindowDeleter> window;
		std::unique_ptr<SDL_Renderer, RendererDeleter> renderer;

		std::unordered_map<AppState, std::unique_ptr<Screen>> screens;
		std::map<std::string, SDL_Texture*> pieceTextures;
		Input input;
		AppState state;
		bool quitProgram;

		std::random_device rd;
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution;
};

#endif
