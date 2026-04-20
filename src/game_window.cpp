#include "game_window.h"

#include <iostream>

static const size_t NUM_OF_PIECES = 12;
static const std::pair<Color, PieceType> keys[] = {
	{Color::WHITE, PieceType::PAWN},
	{Color::BLACK, PieceType::PAWN},
	{Color::WHITE, PieceType::BISHOP},
	{Color::BLACK, PieceType::BISHOP},
	{Color::WHITE, PieceType::KNIGHT},
	{Color::BLACK, PieceType::KNIGHT},
	{Color::WHITE, PieceType::ROOK},
	{Color::BLACK, PieceType::ROOK},
	{Color::WHITE, PieceType::QUEEN},
	{Color::BLACK, PieceType::QUEEN},
	{Color::WHITE, PieceType::KING},
	{Color::BLACK, PieceType::KING}
};

GameWindow::GameWindow(const size_t width, const size_t height) : Window("Chess", width, height) {
	board = new ChessBoard();

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
		SDL_Surface* surface = SDL_LoadBMP(bmp_paths[i]);
		if (!surface) std::cout << "ERROR LOADING BMP SURFACE" << '\n';
		surfaces[i] = surface;
	}

	//create pieceTextures from surfaces
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		pieceTextures[keys[i]] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
	}

	//free paths and surfaces
	for (char* path : bmp_paths) {
		delete path;
	}
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		SDL_DestroySurface(surfaces[i]);
	}

	selectedSquare = Coord();
	gameFinished = false;
	squareSize = 100.0f;
}

void GameWindow::run() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	renderBoardAt(100, 100);
	SDL_RenderPresent(renderer);
}

void GameWindow::renderBoardAt(const size_t x, const size_t y) const {
	for (size_t i = 0; i < 8; ++i ) {
		for (size_t j = 0; j < 8; ++j) {
			(i + j) % 2 == 1 ? SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE)
				: SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);
			SDL_FRect tempRect;
			tempRect.x = x + squareSize * i;
			tempRect.y = y + squareSize * j;
			tempRect.w = squareSize;
			tempRect.h = squareSize;

			SDL_RenderFillRect(renderer, &tempRect);
		}
	}
}

void GameWindow::renderLostPiecesOf(const Color c) const {

}
