#include "rendering.h"
#include "SDL3/SDL.h"
#include <iostream>
#include <map>

const int WINDOW_WIDTH = 850;
const int WINDOW_HEIGHT = 850;
const int PADDING = 25;
const size_t RANK = 8;
const size_t SQUARE_SIZE = 100;
const size_t NUM_OF_PIECES = 12;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_FRect rects[RANK][RANK];
static std::map<std::string, SDL_Texture*> textures;

static ChessBoard* board;
static float mouseX = 0.0f;
static float mouseY = 0.0f;
static Coord selectedSquare = {RANK, RANK};
static std::set<Coord> possibleMoves;
static bool holding = false;

void startApp(ChessBoard* boardPtr) {
	board = boardPtr;
	SDL_CreateWindowAndRenderer("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
	
	//initialize size of squares for UI
	for (int i = 0; i < RANK; ++i) {
		for (int j = 0; j < RANK; ++j) {
			rects[i][j].x = j * SQUARE_SIZE + PADDING;
			rects[i][j].y = i * SQUARE_SIZE + PADDING;
			rects[i][j].w = SQUARE_SIZE;
			rects[i][j].h = SQUARE_SIZE;
		}
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
	Color current = board->getUsersColor();
	int j = (current == Color::WHITE) ? 1 : 0;
	for (size_t i = 0; i < RANK * RANK; ++i) {
		(i + j) % 2 == 0 ? SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE) 
			: SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &rects[i / 8][i % 8]);		
		if (i % 8 == 7) { ++j; }
	}

	//drawing tiles of selected piece
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rects[selectedSquare.x][selectedSquare.y]);

	//drawing tiles of moves piece can take
	for (Coord square : possibleMoves) {
		SDL_RenderFillRect(renderer, &rects[square.x][square.y]);
	}

	//drawing tile if king is in check
	/*
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	if (board->inCheck()) {
		std::pair<int, int> king = board-getCheckedKing();
		SDL_RenderFillRect(renderer, &rects[king.first * 8 + king.second]);
	}
	*/

	//go through all of the board's squares and draw pieces
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (i != selectedSquare.x || j != selectedSquare.y || !holding) {
				Coord pos = {i, j};
				Piece piece = board->getPieceAt(pos);
				if (piece.color != Color::NONE) {
					std::string key = convertPieceToStr(piece);
					SDL_RenderTexture(renderer, textures[key], NULL, &rects[i][j]);
				}
			}
		}
	}

	//Render the piece at the mouse if they're holding it
	if (holding) {
		Piece selectedPiece = board->getPieceAt(selectedSquare);
		if (selectedPiece.color != Color::NONE) {
			SDL_FRect r;
			r.x = mouseX - SQUARE_SIZE / 2;
			r.y = mouseY - SQUARE_SIZE / 2;
			r.w = SQUARE_SIZE;
			r.h = SQUARE_SIZE;
		
			std::string key = convertPieceToStr(selectedPiece);
			SDL_RenderTexture(renderer, textures[key], NULL, &r);
		}
	}

	SDL_RenderPresent(renderer);
}

void stopApp() {
	SDL_Quit();
	//run through all the textures and destruct them	
	for (auto texture : textures) {
			
	}
}

std::string convertPieceToStr(const Piece piece) {
	//We're using this str to get our image path
	std::string str = "";

	switch (piece.color) {
		case Color::WHITE :
			str.push_back('w');
			break;
		case Color::BLACK :
			str.push_back('b');
			break;
		default :
			str.push_back('0');
	}
	
	switch (piece.type) {
		case PieceType::PAWN :
			str.push_back('p');
			break;
		case PieceType::BISHOP :
			str.push_back('b');
			break;
		case PieceType::KNIGHT :
			str.push_back('n');
			break;
		case PieceType::ROOK :
			str.push_back('r');
			break;
		case PieceType::QUEEN :
			str.push_back('q');
			break;
		case PieceType::KING :
			str.push_back('k');
			break;
		default :
			str.push_back('0');
	}

	return str;
}

void setCurrentMousePos(const float x, const float y) {
	mouseX = x;
	mouseY = y;
}

Coord convertMousePosToCoord() {
	SDL_FPoint point = {mouseX, mouseY};
	bool found = false;
	int i = 0;
	int j = 0;
	while (!found && i < 8) {
		j = 0;
		while (!found && j < 8) {
			if (SDL_PointInRectFloat(&point, &rects[i][j])) {
				found = true;
			} else {
				++j;
			}
		}
		if (!found) ++i;	
	}

	return {i, j};
}

void holdPiece() {
	Coord coord = convertMousePosToCoord();

	if (coord.x != 8) {
		Piece piece = board->getPieceAt(coord);
		if (piece.color == board->getWhoseTurnIsIt()) {
			possibleMoves = board->getMovesForPieceAt(coord);
			holding = true;
			selectedSquare = coord;
		}
	}
}

void releasePiece() {
	Coord coord = convertMousePosToCoord();
	if (coord.x != 8 && selectedSquare.x != 8 && selectedSquare != coord 
			&& possibleMoves.find(coord) != possibleMoves.end()) {
		board->movePiece(selectedSquare, coord);
		board->printBoard();

		possibleMoves.clear();
		selectedSquare.x = 8;
		selectedSquare.y = 8;
	}

	holding = false;
}
