#include "widgets.h"

static const size_t TEXT_OFFSET = 5;

Button::Button(size_t x, size_t y, size_t w, size_t h, const std::string& words) {
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = h;
	text = words;
}

void Button::input(const Input& input) {
	if (SDL_PointInRectFloat(&input.mousePos, &area)) {
		if (input.mousePressed) {
			hoveredOver = input.mousePressed;
		}
		wasPressed = input.mouseReleased;
	} else {
		hoveredOver = false;
		wasPressed = false;
	}
}

void Button::renderWithText(SDL_Renderer* renderer, float textScale,
		size_t r, size_t g, size_t b) {
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	hoveredOver ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, r, g, b, 200);
	SDL_RenderFillRect(renderer, &area);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderRect(renderer, &area);
	
	if (text != "") {
		SDL_SetRenderScale(renderer, textScale, textScale);
		SDL_RenderDebugText(renderer, static_cast<int>(area.x / textScale + TEXT_OFFSET),
				static_cast<int>(area.y / textScale + TEXT_OFFSET), text.c_str());
	}
}

void Button::renderWithPiece(SDL_Renderer* renderer, SDL_Texture* piece,
		size_t r, size_t g, size_t b) {
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	hoveredOver ? SDL_SetRenderDrawColor(renderer, 255, 255, 255, 200) 
		: SDL_SetRenderDrawColor(renderer, r, g, b, 200);
	SDL_RenderFillRect(renderer, &area);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
	SDL_RenderRect(renderer, &area);

	if (piece) {
		//do stuff
	}
}

MidGameButtons::MidGameButtons(size_t x, size_t y) : 
	resign(x, y, 100, 50, "Resign"),
	offerDraw(x + 110, y, 100, 50, "Offer Draw"),
	acceptDraw(x + 220, y, 100, 50, "Accept Draw"),
	declineDraw(x + 330, y, 100, 50, "Decline Draw") {}

void MidGameButtons::input(const Input& input) {
	resign.input(input);
	if (!disableOfferingDraw) offerDraw.input(input);
	if (drawWasOffered) {
		acceptDraw.input(input);
		declineDraw.input(input);
	}
}

void MidGameButtons::render(SDL_Renderer* renderer) {
	resign.renderWithText(renderer, 2.0f, 0, 0, 255);
	if (!disableOfferingDraw) {
		offerDraw.renderWithText(renderer, 2.0f);
	}
	
	if (drawWasOffered) {
		acceptDraw.renderWithText(renderer, 2.0f, 0, 255, 0);	
		declineDraw.renderWithText(renderer, 2.0f, 255, 0, 0);
	}
}


