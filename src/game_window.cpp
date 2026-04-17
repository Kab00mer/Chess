#include "game_window.h"

GameWindow::GameWindow() {
	board = new ChessBoard();
	SDL_CreateWindowAndRenderer("Chess", windowWidth, windowHeight, 0, &window, &renderer);

	std::string basePath = SDL_GetBasePath();
	//print basePath = basePath.substr(0, basePath.length() - 6);
	/*
	basePath = basePath.substr(0, basePath.length() - 6);
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
	*/

	selectedSquare = Coord();
	mouseX = 0;
	mouseY = 0;
	gameFinished = false;
	userQuit = false;
}

void GameWindow::gameLoop() {
	{
		SDL_Event event;	
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				userQuit = true;
			}

			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				//mousePressed();
			} else if (event.type == SDL_EVENT_MOUSE_MOTION) {
				//setCurrentMousePos(event.button.x, event.button.y);
			} else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				//mouseReleased();
			} else if (event.type == SDL_EVENT_KEY_DOWN) {
				//maybe do something with this later
			}
		}
	}

	
}
