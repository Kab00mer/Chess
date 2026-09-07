#ifndef WIDGETS_H
#define WIDGETS_H

#include "screen.h"

#include <string>
#include <vector>
#include <iostream>

struct Button {
	SDL_FRect area;
	std::string text = "";
	SDL_Texture* piece = nullptr;

	bool hoveredOver = false;
	bool wasPressed = false;

	Button(size_t, size_t, size_t, size_t, const std::string&);
	void input(const Input&);
	void renderWithText(SDL_Renderer*, float, size_t r = 150, 
			size_t g = 150, size_t b = 150);
	void renderWithPiece(SDL_Renderer*, SDL_Texture*,
			size_t r = 150, size_t g = 150, size_t b = 150);
};

struct MidGameButtons {
	Button resign;
	Button offerDraw;
	Button acceptDraw;
	Button declineDraw;

	bool disableOfferingDraw = false;
	bool drawWasOffered = false;

	MidGameButtons(size_t, size_t);
	void input(const Input&);
	void render(SDL_Renderer*);
};

/*
struct Clock {
	size_t timeLeft;

	Clock(size_t);
	void render(SDL_Renderer*);
};

struct PiecesTaken {
	std::vector<std::string> pieces;
	size_t totalPoints;
	size_t opponentsPoints;

	void recalulatePoints();
	void render(SDL_Renderer);
};

struct PromotionScreen {
	Button bishop;
	Button knight;
	Button rook;
	Button queen;

	void input(const Input&);
	void render(SDL_Renderer*);
};

struct EndingScreen {
	void input(const Input&);
	void render(SDL_Renderer*);
};
*/

#endif
