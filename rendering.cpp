#include <SDL3/SDL.h>
#include "board.h"

const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 1300;
const size_t PADDING = 50;
const size_t NUM_OF_SQUARES = 64;
const size_t SQAURE_SIZE = 150;
const size_t NUM_OF_PIECES = 12;

static SDL_Window* window;
static SDL_Renderer* renderer;

static SDL_FRect rects[NUM_OF_SQUARES];
static SDL_Texture textures[NUM_OF_SQUARES];

public startApp() {
	SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		rect[i].x = (i % 8) * SQUARE_SIZE + PADDING;
		rect[i].y = static_cast<size_t>(i / 8) * SQUARE_SIZE + PADDING;
		rect[i].w = SQUARE_SIZE;
		rect[i].h = SQUARE_SIZE;
	}
}

public void renderBoard(bool isPlayerWhite, ChessBoard& board) {
	renderSquares(isPlayerWhite);
	renderPieces(board);	
	SDL_RendererPresent(renderer);
}

private void renderSquares(bool white) {
	size_t i = white ? 0 : 1
	SDL_SetRendererDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	while (i < NUM_OF_SQUARES) {
		SDL_RenderFIllRect(renderer, rects[i]);		
		i += 2;
	}
	
	i -= NUMS_OF_SQAURES;
	SDL_SetRendererDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	while (i < NUM_OF_SQUARES) {
		SDL_RenderFIllRect(renderer, rects[i]);		
		i += 2;
	}
}

private void renderPieces(board) {
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		//have board return if there's a piece there
		//render a texture based on the piece
	}
}

public void stopApp() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
