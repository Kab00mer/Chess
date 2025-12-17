#include "rendering.h"
#include "SDL3/SDL.h"
#include <map>
#include <iostream>

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
static std::pair<int, int> mousePos = {8, 8};
static std::pair<int, int> selectedSquare = {8, 8};

void startApp(ChessBoard* boardPtr) {
	board = boardPtr;
	SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	
	//initialize size of squares for UI
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		//std::cout << "(" << i % 8 << ", " << static_cast<size_t>(i / 8) << ")" << '\n';
		rects[i].x = (i % 8) * SQUARE_SIZE + PADDING;
		rects[i].y = static_cast<size_t>(i / 8) * SQUARE_SIZE + PADDING;
		rects[i].w = SQUARE_SIZE;
		rects[i].h = SQUARE_SIZE;
	}

	//loading image paths 
	std::string basePath = SDL_GetBasePath();
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
		//std::cout << bmp_paths[i] << '\n';
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
}

void continueApp() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_RenderClear(renderer);

	//drawing checkered squares
	size_t j = board->isUserWhite() ? 1 : 0; //switch this depending on the users color
	for (size_t i = 0; i < NUM_OF_SQUARES; ++i) {
		(i + j) % 2 == 0 ? SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE) 
			: SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rects[i]);		
		if (i % 8 == 7) { ++j; }
	}

	//go through all of the board's squares and draw pieces
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			if (i != selectedSquare.first || j != selectedSquare.second) {
				std::pair<char, char> piece = board->getPieceAt(i, j);
				//std::cout << piece.first << piece.second << '\n';
				renderPieceAt(piece.first, piece.second, i, j);
			}
		}
	}

	//Render stuff for the selected piece
	if (selectedSquare.first != 8) {
		std::pair<char, char> selectedPiece = board->getPieceAt(selectedSquare.first, selectedSquare.second);
		renderPieceAt(selectedPiece.first, selectedPiece.second, mousePos.first, mousePos.second);
	}

	SDL_RenderPresent(renderer);
}

void stopApp() {
	SDL_Quit();
	//run through all the textures and destruct them	
}

void renderPieceAt(char color, char type, int x, int y) {
	if (color != '0') {
			std::string str = "";
			str.push_back(color);
			str.push_back(type);
			SDL_RenderTexture(renderer, textures[str], NULL, &rects[x * 8 + y]);
	}
}

void setCurrentMousePos(const SDL_FPoint& point) {
	//converts SDL's point to a coordinate
	bool found = false;
	int i = 0;
	int j = 0;
	while (!found && i < 8) {
		j = 0;
		while (!found && j < 8) {
			if (SDL_PointInRectFloat(&point, &rects[i * 8 + j])) {
				found = true;
			} else {
				++j;
			}
		}
		if (!found) ++i;	
	}
	std::cout << i << ", " << j << '\n';
	mousePos = std::make_pair(i, j);
}

void selectPiece() {
	selectedSquare = mousePos;	
}

void releasePiece() {
	if (selectedSquare != mousePos) {
		board->movePiece(selectedSquare.first, selectedSquare.second, mousePos.first, mousePos.second);
	} 
}
