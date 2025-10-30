#include <SDL3/SDL.h>

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;
const size_t PADDING = 50;
const size_t NUM_OF_SQUARES = 64;
const size_t SQAURE_SIZE = 100;

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_FRect rects[NUM_OF_SQUARES];

void createApp() {
	SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		rect[i].x = (i % 8) * SQUARE_SIZE + PADDING;
		rect[i].y = static_cast<size_t>(i / 8) * SQUARE_SIZE + PADDING;
		rect[i].w = SQUARE_SIZE;
		rect[i].h = SQUARE_SIZE;
	}
}

bool renderBoard(bool userIsWhite) {
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_FRect rects[64];
	size_t tile = userIsWhite ? 0 : 1;
	while (tile < 64) {
		rects[tile].x = 
		rects[tile].y = 
		rects[tile]

		tile += 2;
	}
}

void destructRendering() {

}
