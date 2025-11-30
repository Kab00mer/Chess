#include "rendering.h"
#include "SDL3/SDL.h"
#include <map>

const int WINDOW_WIDTH = 850;
const int WINDOW_HEIGHT = 850;
const int PADDING = 25;
const size_t NUM_OF_SQUARES = 64;
const size_t SQUARE_SIZE = 100;
const size_t NUM_OF_PIECES = 12;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_FRect rects[NUM_OF_SQUARES];
static std::map<std::string, SDL_Texture*> textures;

static ChessBoard* board;

void startApp(ChessBoard* boardPtr) {
	board = boardPtr;
	SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	
	//initialize size of squares for UI
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		rects[i].x = (i % 8) * SQUARE_SIZE + PADDING;
		rects[i].y = static_cast<size_t>(i / 8) * SQUARE_SIZE + PADDING;
		rects[i].w = SQUARE_SIZE;
		rects[i].h = SQUARE_SIZE;
	}

	//loading image paths 
	char* bmp_paths[NUM_OF_PIECES];
	SDL_asprintf(&(bmp_paths[0]), "%simages/wp", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[1]), "%simages/bp", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[2]), "%simages/wb", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[3]), "%simages/bb", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[4]), "%simages/wn", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[5]), "%simages/bn", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[6]), "%simages/wr", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[7]), "%simages/br", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[8]), "%simages/wq", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[9]), "%simages/bq", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[10]), "%simages/wk", SDL_GetBasePath());
	SDL_asprintf(&(bmp_paths[11]), "%simages/bk", SDL_GetBasePath());

	//image paths must be loaded to surfaces and freed
	SDL_Surface* surfaces[NUM_OF_PIECES];
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		surfaces[i] = SDL_LoadBMP(bmp_paths[i]);
		SDL_free(bmp_paths[i]);
	}

	//create textures from surfaces
	textures["wp"] = SDL_CreateTextureFromSurface(renderer, surfaces[0]);
	textures["bp"] = SDL_CreateTextureFromSurface(renderer, surfaces[1]);
	textures["wb"] = SDL_CreateTextureFromSurface(renderer, surfaces[2]);
	textures["bb"] = SDL_CreateTextureFromSurface(renderer, surfaces[3]);
	textures["wn"] = SDL_CreateTextureFromSurface(renderer, surfaces[4]);
	textures["bn"] = SDL_CreateTextureFromSurface(renderer, surfaces[5]);
	textures["wr"] = SDL_CreateTextureFromSurface(renderer, surfaces[6]);
	textures["br"] = SDL_CreateTextureFromSurface(renderer, surfaces[7]);
	textures["wq"] = SDL_CreateTextureFromSurface(renderer, surfaces[8]);
	textures["bq"] = SDL_CreateTextureFromSurface(renderer, surfaces[9]);
	textures["wk"] = SDL_CreateTextureFromSurface(renderer, surfaces[10]);
	textures["bk"] = SDL_CreateTextureFromSurface(renderer, surfaces[11]);

	//free surfaces
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		SDL_DestroySurface(surfaces[i]);
	}
}

void continueApp() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_RenderClear(renderer);

	//drawing checkered squares
	size_t j = 0;
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		(i + j) % 2 == 0 ? SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE) 
			: SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rects[i]);		
		if (i % 8 == 7) { ++j; }
	}

	//go through all of the board's squares and draw pieces
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			std::string piece = board->getPieceAt(i, j);

			if (piece != "") {
				SDL_FRect rect;
				rect.x = SQUARE_SIZE * i + PADDING;
				rect.y = SQUARE_SIZE * j + PADDING;
				rect.w = SQUARE_SIZE;
				rect.h = SQUARE_SIZE;

				SDL_RenderTexture(renderer, textures[piece], NULL, &rect);
			}					
		}
	}

	SDL_RenderPresent(renderer);
}

void stopApp() {
	SDL_Quit();
	//run through all the textures and destruct them	
}
