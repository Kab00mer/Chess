#ifndef CHESS_APP_H
#define CHESS_APP_H

#include "resources/screen.h"

#include <unordered_map>
#include <memory>

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
			
		void mainLoop();

		bool getQuitProgram();
		
	private:
		void readInput();
		
		std::unique_ptr<SDL_Window, WindowDeleter> window;
		std::unique_ptr<SDL_Renderer, RendererDeleter> renderer;

		std::unordered_map<AppState, std::unique_ptr<Screen>> screens;
		Input input;
		AppState state;
		bool quitProgram;
};

#endif
