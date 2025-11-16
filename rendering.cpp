#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
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

static void loadBoardAndAssets() {
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		rects[i].x = (i % 8) * SQUARE_SIZE + PADDING;
		rects[i].y = static_cast<size_t>(i / 8) * SQUARE_SIZE + PADDING;
		rects[i].w = SQUARE_SIZE;
		rects[i].h = SQUARE_SIZE;
	}

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
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		surfaces[i] = SDL_LoadPNG(png_paths[i]);
		SDL_free(png_paths[i]);
	}

	textures[std::make_pair(PieceType::P, Color::White)] = SDL_CreateTextureFromSurface(renderer, surfaces[0]);
	textures[std::make_pair(PieceType::P, Color::Black)] = SDL_CreateTextureFromSurface(renderer, surfaces[1]);
	textures[std::make_pair(PieceType::B, Color::White)] = SDL_CreateTextureFromSurface(renderer, surfaces[2]);
	textures[std::make_pair(PieceType::B, Color::Black)] = SDL_CreateTextureFromSurface(renderer, surfaces[3]);
	textures[std::make_pair(PieceType::N, Color::White)] = SDL_CreateTextureFromSurface(renderer, surfaces[4]);
	textures[std::make_pair(PieceType::N, Color::Black)] = SDL_CreateTextureFromSurface(renderer, surfaces[5]);
	textures[std::make_pair(PieceType::R, Color::White)] = SDL_CreateTextureFromSurface(renderer, surfaces[6]);
	textures[std::make_pair(PieceType::R, Color::Black)] = SDL_CreateTextureFromSurface(renderer, surfaces[7]);
	textures[std::make_pair(PieceType::Q, Color::White)] = SDL_CreateTextureFromSurface(renderer, surfaces[8]);
	textures[std::make_pair(PieceType::Q, Color::Black)] = SDL_CreateTextureFromSurface(renderer, surfaces[9]);
	textures[std::make_pair(PieceType::K, Color::White)] = SDL_CreateTextureFromSurface(renderer, surfaces[10]);
	textures[std::make_pair(PieceType::K, Color::Black)] = SDL_CreateTextureFromSurface(renderer, surfaces[11]);
	
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		SDL_DestroySurface(surfaces[i]);
	}
}

static void drawNewBoard() {
	size_t j = 0;
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		(i + j) % 2 == 0 ? SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) 
			: SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rects[i]);		
		if (i % 8 == 7) { ++j; }
	}

	for (size_t i = 0; i < 8; ++i) {
		SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::P, Color::White)], &rects[8 + i]);
		SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::P, Color::Black)], &rects[48 + i]);
	}
	
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::R, Color::White)], &rects[0]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::R, Color::White)], &rects[7]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::R, Color::Black)], &rects[56]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::R, Color::Black)], &rects[63]);

	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::N, Color::White)], &rects[1]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::N, Color::White)], &rects[6]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::N, Color::Black)], &rects[57]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::N, Color::Black)], &rects[62]);

	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::B, Color::White)], &rects[2]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::B, Color::White)], &rects[5]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::B, Color::Black)], &rects[58]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::B, Color::Black)], &rects[61]);

	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::Q, Color::White)], &rects[3]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::Q, Color::Black)], &rects[59]);

	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::K, Color::White)], &rects[4]);
	SDL_RenderTexture(renderer, textures[std::make_pair(PieceType::K, Color::Black)], &rects[60]);
}

void startApp() {
	SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 200);
	SDL_RenderClear(renderer);

	loadBoardAndAssets();
	drawNewBoard();

	SDL_RenderPresent(renderer);
}

void stopApp() {
	SDL_Quit();
	//run through all the textures and destruct them	
}
