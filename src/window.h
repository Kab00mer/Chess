#ifndef WINDOW_H
#define WINDOW_H

#include "SDL3/SDL.h"

#include <string>

class Window {
	public:
		Window(const char* name = "Window", const size_t width = 900, const size_t height = 900);
		~Window();

		void readInput();
		virtual void run();
		bool didUserQuit() const;

	protected:
		SDL_Window* window;
		SDL_Renderer* renderer;

		bool mousePressed;
		bool mouseReleased;
		bool userQuit;

		float mouseX;
		float mouseY;
};

#endif
