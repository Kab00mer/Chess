#include "game_window.h"

#include <iostream>

static const size_t NUM_OF_PIECES = 12;

GameWindow::GameWindow() : Window("Chess") {
	board = new ChessBoard();

	std::string basePath = SDL_GetBasePath();
	basePath = basePath.substr(0, basePath.length() - 6);
	std::cout << basePath << '\n';
	const char* projectRoot = basePath.c_str();

	char* bmp_paths[NUM_OF_PIECES];
	SDL_asprintf(&(bmp_paths[0]), "%simages/wp.bmp", projectRoot);
	SDL_asprintf(&(bmp_paths[1]), "%simages/bp.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[2]), "%simages/wb.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[3]), "%simages/bb.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[4]), "%simages/wn.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[5]), "%simages/bn.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[6]), "%simages/wr.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[7]), "%simages/br.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[8]), "%simages/wq.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[9]), "%simages/bq.bmp", projectRoot);
	SDL_asprintf(&(bmp_paths[10]), "%simages/wk.bmp", projectRoot); 
	SDL_asprintf(&(bmp_paths[11]), "%simages/bk.bmp", projectRoot); 

	//image paths must be loaded to surfaces
	SDL_Surface* surfaces[NUM_OF_PIECES];
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		SDL_Surface* surface = SDL_LoadBMP(bmp_paths[i]);
		if (!surface) std::cout << "ERROR LOADING BMP SURFACE" << '\n';
		surfaces[i] = surface;
	}

	//create pieceTextures from surfaces
	pieceTextures["wp"] = SDL_CreateTextureFromSurface(renderer, surfaces[0]);
	pieceTextures["bp"] = SDL_CreateTextureFromSurface(renderer, surfaces[1]);
	pieceTextures["wb"] = SDL_CreateTextureFromSurface(renderer, surfaces[2]);
	pieceTextures["bb"] = SDL_CreateTextureFromSurface(renderer, surfaces[3]);
	pieceTextures["wn"] = SDL_CreateTextureFromSurface(renderer, surfaces[4]);
	pieceTextures["bn"] = SDL_CreateTextureFromSurface(renderer, surfaces[5]);
	pieceTextures["wr"] = SDL_CreateTextureFromSurface(renderer, surfaces[6]);
	pieceTextures["br"] = SDL_CreateTextureFromSurface(renderer, surfaces[7]);
	pieceTextures["wq"] = SDL_CreateTextureFromSurface(renderer, surfaces[8]);
	pieceTextures["bq"] = SDL_CreateTextureFromSurface(renderer, surfaces[9]);
	pieceTextures["wk"] = SDL_CreateTextureFromSurface(renderer, surfaces[10]);
	pieceTextures["bk"] = SDL_CreateTextureFromSurface(renderer, surfaces[11]);

	//free surfaces
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		SDL_DestroySurface(surfaces[i]);
	}

	selectedSquare = Coord();
	gameFinished = false;
	squareSize = 100.0f;
}

GameWindow::~GameWindow() {
	auto iter = pieceTextures.begin();
	auto end = pieceTextures.end();
	while (iter != end) {
		SDL_DestroyTexture(pieceTextures[iter->first]);
		++iter;
	}
}

void GameWindow::run() {
	SDL_SetRenderDrawColor(renderer, SDL_rand(256), SDL_rand(256), SDL_rand(256), 200);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

