#include "rendering.h"
#include "robots.h"
#include "SDL3/SDL.h"
#include <iostream>
#include <map>
#include <chrono>
#include <thread>

const int WINDOW_WIDTH = 850;
const int WINDOW_HEIGHT = 850;
const int PADDING = 25;
const size_t RANK = 8;
const size_t SQUARE_SIZE = 100;
const size_t NUM_OF_PIECES = 12;

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_FRect rects[RANK][RANK];
static SDL_FRect promotionRects[4];
static std::map<std::string, SDL_Texture*> textures;

static ChessBoard* board;
static Piece boardState[RANK][RANK];
static float mouseX = 0.0f;
static float mouseY = 0.0f;
static Coord selectedSquare = {RANK, RANK};
static std::set<Coord> possibleMoves;
static bool holding = false;
static bool promotionScreen = false;
static Coord promotionSquare;
static Piece promotionPieces[] = {
	Piece(Color::NONE, PieceType::BISHOP), 
	Piece(Color::NONE, PieceType::KNIGHT),
	Piece(Color::NONE, PieceType::ROOK), 
	Piece(Color::NONE, PieceType::QUEEN)
};
static bool robotPause = false;
static bool finished = false;

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
	
	//initialize boardState
	for (int i = 0; i < RANK; ++i) {
		for (int j = 0; j < RANK; ++j) {
			boardState[i][j] = board->getPieceAt({i, j});
		}
	}

	//setting up the promotion board
	for (int i = 0; i < 4; ++i) {
		promotionRects[i] = rects[3][2 + i];
	}

	//setup robots
	initiateRobots(board);
	//robotPause = true;
	//tryToMoveBot();
}

void continueApp() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 200);
	SDL_RenderClear(renderer);

	if (!promotionScreen) {
		//drawing checkered squares
		Color current = board->getUsersColor();
		int j = (current == Color::WHITE) ? 1 : 0;
		for (size_t i = 0; i < RANK * RANK; ++i) {
			(i + j) % 2 == 0 ? SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE) 
				: SDL_SetRenderDrawColor(renderer, 220, 220, 220, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &rects[i / 8][i % 8]);		
			if (i % 8 == 7) { ++j; }
		}

		//drawing tiles of previous move
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
		Move previous = board->getMostRecentMove();
		if (previous.from.x != 8) {
			drawHighlightAt(previous.from.x, previous.from.y);
			drawHighlightAt(previous.to.x, previous.to.y);
		}

		//drawing tile of selected piece
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		if (selectedSquare.x != 8) {
			drawHighlightAt(selectedSquare.x, selectedSquare.y);
		}

		//drawing tiles of moves piece can take
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		for (Coord square : possibleMoves) {
			drawHighlightAt(square.x, square.y);
		}

		//drawing tile if king is in check
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		if (board->getIfInCheck()) {
			bool found = false;
			int i = 0;
			int j = 0;
			while (!found && i < RANK) {
				j = 0;
				while (!found && j < RANK) {
					if (boardState[i][j].color == board->getWhoseTurnIsIt() 
							&& boardState[i][j].type == PieceType::KING) {
						found = true;
					} else {
						++j;
					}
				}
				if (!found) { ++i; }
			}

			drawHighlightAt(i, j);
		}

		//go through all of the board's squares and draw pieces
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (i != selectedSquare.x || j != selectedSquare.y || !holding) {
					if (boardState[i][j].color != Color::NONE) {
						std::string key = convertPieceToStr(boardState[i][j]);
						SDL_RenderTexture(renderer, textures[key], NULL, &rects[i][j]);
					}
				}
			}
		}

		//Render the piece at the mouse if they're holding it
		if (holding) {
			Piece selectedPiece = boardState[selectedSquare.x][selectedSquare.y];
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

	} else {
		//draw promotion screen
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
		Color current = board->getWhoseTurnIsIt();
		int counter = 0;

		for (Piece p : promotionPieces) {
			promotionPieces[counter].color = current;
			SDL_RenderFillRect(renderer, &promotionRects[counter]);
			std::string key = convertPieceToStr(p);
			SDL_RenderTexture(renderer, textures[key], NULL, &promotionRects[counter]);
			++counter;
		}
	}

	SDL_RenderPresent(renderer);
	
	//This is if I want there to be a delay for bot moves
	if (robotPause && !finished) { 
		robotPause = false;
		std::this_thread::sleep_for(std::chrono::seconds(0));
		tryToMoveBot(); 
	}
}

void stopApp() {
	SDL_Quit();
	//run through all the textures and destruct them	
	for (auto texture : textures) {
			
	}
}

void drawHighlightAt(const int x, const int y) {
	SDL_FRect r;
	r.x = rects[x][y].x + SQUARE_SIZE / 6;
	r.y = rects[x][y].y + SQUARE_SIZE / 6;
	r.w = SQUARE_SIZE / 1.5;
	r.h = SQUARE_SIZE / 1.5;
	SDL_RenderFillRect(renderer, &r);
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
	if (!promotionScreen) {
		Coord coord = convertMousePosToCoord();

		if (coord.x != 8) {
			if (boardState[coord.x][coord.y].color == board->getWhoseTurnIsIt()) {
				possibleMoves = board->getMovesForPieceAt(coord);
				holding = true;
				selectedSquare = coord;
			} else if (possibleMoves.find(coord) == possibleMoves.end()) {
				possibleMoves.clear();
				selectedSquare = {8, 8};
			}
		}
	}
}

void releasePiece() {
	if (promotionScreen) {
		SDL_FPoint point = {mouseX, mouseY};
		bool found = false;
		int counter = 0;
		while (!found && counter < 4) {
			SDL_PointInRectFloat(&point, &promotionRects[counter]) ? found = true : ++counter;
		}

		if (found) {
			board->setNextPawnPromotion(promotionPieces[counter].type);
			promotionScreen = false;

			board->movePiece(selectedSquare, promotionSquare, false);
			updateBoard();
			if (!board->getIfMated()) { robotPause = true; }

			promotionSquare = {8, 8};
		}

	} else {
		Coord coord = convertMousePosToCoord();
		if (possibleMoves.find(coord) != possibleMoves.end() || selectedSquare == coord) {
			if (coord.x != 8 && selectedSquare.x != 8 && selectedSquare != coord) {
				if (boardState[selectedSquare.x][selectedSquare.y].type == PieceType::PAWN 
						&& (coord.x == 7 || coord.x == 0)) {
					promotionScreen = true;
					promotionSquare = coord;
				} else {
					board->movePiece(selectedSquare, coord, false);
					updateBoard();	
					if (!board->getIfMated()) { robotPause = true; }
				}
			}
		} else {
			possibleMoves.clear();
			selectedSquare = {8, 8};
		}

		holding = false;
	}
}

void keyPressed() {
	board->undoMove();
	updateBoard();
}

void updateBoard() {
	board->printBoard();

	if (board->getIfMated()) {
		std::cout << "CHECKMATE" << '\n';
		board->getWhoseTurnIsIt() == Color::WHITE ? std::cout << "BLACK" : std::cout << "WHITE";
		std::cout << " HAS WON!!!" << '\n';
		finished = true;

	} else if (board->getIfDraw().first) {
		std::cout << board->getIfDraw().second << '\n' << "GAME IS A DRAW!!!" << '\n';
		finished = true;
	}

	for (int i = 0; i < RANK; ++i) {
		for (int j = 0; j < RANK; ++j) {
			boardState[i][j] = board->getPieceAt({i, j});
		}
	}

	possibleMoves.clear();
	selectedSquare = {8, 8};
	//tryToMoveBot();
}

void tryToMoveBot() {
	if (!finished) { 
		//randomRobot(); 
		pointRobot(1);
	}
	updateBoard();
}
