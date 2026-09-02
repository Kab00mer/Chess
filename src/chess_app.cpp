#include "chess_app.h"
#include "menus/main_menu.h"
#include "menus/local_menu.h"
#include "menus/computer_menu.h"
#include "menus/online_menu.h"
#include "games/local_game.h"
#include "games/computer_game.h"
#include "games/online_game.h"

#include <iostream>

static const size_t STRETCHED_WINDOW_WIDTH = 1280;
static const size_t TRUE_WINDOW_WIDTH = 640;
static const size_t STRETCHED_WINDOW_HEIGHT = 720;
static const size_t TRUE_WINDOW_HEIGHT = 360;

static const size_t NUM_OF_PIECES = 12;

ChessApp::ChessApp() : generator(rd()), distribution(0, 1) {
	quitProgram = false;

	window.reset(SDL_CreateWindow("Chess App", STRETCHED_WINDOW_WIDTH, STRETCHED_WINDOW_HEIGHT, 
			SDL_WINDOW_RESIZABLE));
	renderer.reset(SDL_CreateRenderer(window.get(), nullptr));

	//sets SDL's Coord system to be 640 by 360 and strech depending on how big the window is
	SDL_SetRenderLogicalPresentation(renderer.get(), TRUE_WINDOW_WIDTH, 
			TRUE_WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	screens[AppState::MAIN_MENU] = std::make_unique<MainMenu>();
	screens[AppState::LOCAL_MENU] = std::make_unique<LocalMenu>();
	screens[AppState::COMPUTER_MENU] = std::make_unique<ComputerMenu>();
	screens[AppState::ONLINE_MENU] = std::make_unique<OnlineMenu>();
	screens[AppState::LOCAL_GAME] = nullptr;
	screens[AppState::COMPUTER_GAME] = nullptr;
	screens[AppState::ONLINE_GAME] = nullptr;

	state = AppState::MAIN_MENU;

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
	pieceTextures["wp"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[0]);
	pieceTextures["bp"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[1]);
	pieceTextures["wb"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[2]);
	pieceTextures["bb"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[3]);
	pieceTextures["wn"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[4]);
	pieceTextures["bn"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[5]);
	pieceTextures["wr"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[6]);
	pieceTextures["br"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[7]);
	pieceTextures["wq"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[8]);
	pieceTextures["bq"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[9]);
	pieceTextures["wk"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[10]);
	pieceTextures["bk"] = SDL_CreateTextureFromSurface(renderer.get(), surfaces[11]);

	//free surfaces
	for (size_t i = 0; i < NUM_OF_PIECES; ++i) {
		SDL_DestroySurface(surfaces[i]);
	}
}

ChessApp::~ChessApp() {
	auto iter = pieceTextures.begin();
	auto end = pieceTextures.end();
	while (iter != end) {
		SDL_DestroyTexture(pieceTextures[iter->first]);
		++iter;
	}	
}

void ChessApp::mainLoop() {
	readInput();
		
	screens[state]->processInput(input);
	screens[state]->processRender(renderer.get(), pieceTextures);

	if (screens[state]->getUserExited()) {
		quitProgram = true;
		return;
	}

	AppState nextState = screens[state]->getNextState();
	if (nextState != AppState::NONE) {
		screens[state]->setNextState(AppState::NONE);

		WhoGoesFirst turnOrder = screens[state]->getWhoFirst();
		if (turnOrder == WhoGoesFirst::RANDOM) {
			turnOrder = distribution(generator) ? WhoGoesFirst::LEFT_FIRST : WhoGoesFirst::RIGHT_FIRST;
		}
		size_t timeControl = screens[state]->getTimeControl();

		switch (nextState) {
			case AppState::LOCAL_GAME:
				//fix later by writing unique getters for each type of menu/game
				screens[AppState::LOCAL_GAME] = std::make_unique<LocalGame>();
				screens[AppState::LOCAL_GAME]->setWhoFirst(turnOrder);
				screens[AppState::LOCAL_GAME]->setTimeControl(timeControl);
				state = nextState;
				break;

			case AppState::COMPUTER_GAME:
				//fix later by writing unique getters for each type of menu/game
				screens[AppState::COMPUTER_GAME] = std::make_unique<ComputerGame>();
				screens[AppState::COMPUTER_GAME]->setWhoFirst(turnOrder);
				state = nextState;
				break;

			case AppState::ONLINE_GAME:
				//fix later by writing unique getters for each type of menu/game
				screens[AppState::ONLINE_GAME] = std::make_unique<OnlineGame>();
				screens[AppState::ONLINE_GAME]->setTimeControl(timeControl);
				state = nextState;
				break;

			default:
				if (state == AppState::LOCAL_GAME || state == AppState::COMPUTER_GAME
						|| state == AppState::ONLINE_GAME) {
					screens[state].reset();
				}
				state = nextState;
		}
	}
}

bool ChessApp::getQuitProgram() { return quitProgram; }

void ChessApp::readInput() {
	input.textInput.clear();
	input.backspace = false;
	input.enter = false;
	input.mousePressed = false;
	input.mouseReleased = false;

	int windowX, windowY;
	SDL_GetWindowSize(window.get(), &windowX, &windowY);
	float windowScaleX = TRUE_WINDOW_WIDTH / static_cast<float>(windowX);
	float windowScaleY = TRUE_WINDOW_HEIGHT / static_cast<float>(windowY);

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		input.mousePos = {event.button.x * windowScaleX, event.button.y * windowScaleY };

		switch (event.type) {
			case SDL_EVENT_QUIT:
				quitProgram = true;
				break;

			case SDL_EVENT_TEXT_INPUT:
				input.textInput += event.text.text;
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				input.mousePressed = true;
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP:
				input.mouseReleased = true;
				break;
		}
	}
}
