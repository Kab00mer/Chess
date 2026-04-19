#include "window.h"

Window::Window(const char* name, const size_t width, const size_t height) {
	SDL_CreateWindowAndRenderer(name, width, height, 0, &window, &renderer);

	mousePressed = false;
	mouseReleased = false;
	userQuit = false;

	mouseX = 0.0f;
	mouseY = 0.0f;
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Window::readInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		userQuit = event.type == SDL_EVENT_QUIT;
		mousePressed = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
		mouseReleased = event.type == SDL_EVENT_MOUSE_BUTTON_UP;

		if (event.type == SDL_EVENT_MOUSE_MOTION) {
			mouseX = event.button.x;
			mouseY = event.button.y;
		}
	}
}

void Window::run() {};

bool Window::didUserQuit() const { return userQuit; }
