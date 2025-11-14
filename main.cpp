#include <SDL3/SDL.h>
#include "board.h"
#include <map>

const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 900;
const size_t PADDING = 50;
const size_t NUM_OF_SQUARES = 64;
const size_t SQUARE_SIZE = 100;
const size_t NUM_OF_PIECES = 12;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_FRect rects[NUM_OF_SQUARES];
static std::map<std::pair<PieceType, Color>, std::unique_ptr<SDL_Texture>> textures;

int main(int argc, char* argv[]) {
	ChessBoard board;

	SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 200);
	SDL_RenderClear(renderer);

	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		rects[i].x = (i % 8) * SQUARE_SIZE + PADDING;
		rects[i].y = static_cast<size_t>(i / 8) * SQUARE_SIZE + PADDING;
		rects[i].w = SQUARE_SIZE;
		rects[i].h = SQUARE_SIZE;
	}

	size_t j = 0;
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		(i + j) % 2== 0 ? SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) 
			: SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rects[i]);		
		if (i % 8 == 7) { ++j; }
	}

	SDL_RenderPresent(renderer);

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
	}

	SDL_Quit();
	return 0;
}

void loadTextures() {
	char* png_paths[NUM_OF_PIECES];
	SDL_asprintf(&(png_paths[0]), "%simages/wp", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[1]), "%simages/bp", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[2]), "%simages/wb", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[3]), "%simages/bb", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[4]), "%simages/wn", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[5]), "%simages/bn", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[6]), "%simages/wr", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[7]), "%simages/br", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[8]), "%simages/wq", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[9]), "%simages/bq", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[10]), "%simages/wk", SDL_GetBasePath());
	SDL_asprintf(&(png_paths[11]), "%simages/bk", SDL_GetBasePath());

	SDL_Surface* surfaces[NUM_OF_PIECES];
	for (int i = 0; i < NUM_OF_PIECES; ++i) {
		surfaces[i] = SDL_LoadPNG(png_paths[i]);
		SDL_free(png_paths[i]);
	}

	textures[std::make_pair(PieceType::Pawn, Color::White)] = SDL_CreateTextureFromSurface(renderer, surfaces[0]);
	//do the other 11
	
	for (int i = 0; i < NUM_OF_PIECES; ++i) {
		SDL_DestroySurface(surfaces[i]);
	}
}

void renderPieces(ChessBoard& board) {
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		for (size_t j = 0; j < NUM_OF_SQUARES; ++i) {
			std::pair<PieceType, Color> piece = board.returnPieceAt(std::pair(i, j)); 
		}
	}
}
