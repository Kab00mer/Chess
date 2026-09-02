#include "local_game.h"

#include <iostream>

static const size_t WINDOW_WIDTH = 640;
static const size_t WINDOW_HEIGHT = 360;
static const size_t PADDING = 10;
static const size_t SQUARE_SIZE = 36;
static const size_t CENTER_PADDING = 44;

LocalGame::LocalGame() {
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			leftBoard[i][j].x = PADDING + SQUARE_SIZE * i;
			leftBoard[i][j].y = PADDING + SQUARE_SIZE * j;
			leftBoard[i][j].w = SQUARE_SIZE;
			leftBoard[i][j].h = SQUARE_SIZE;

			rightBoard[i][j].x = PADDING + 8 * SQUARE_SIZE + SQUARE_SIZE * i + CENTER_PADDING;
			rightBoard[i][j].y = PADDING + SQUARE_SIZE * j;
			rightBoard[i][j].w = SQUARE_SIZE; 
			rightBoard[i][j].h = SQUARE_SIZE;
		}
	}

	//promotionScreen
	inPromotionScreen = false;
	pieceBeingHeld = {};
	whoseTurnIsIt = Color::WHITE;
	previousMove = {};
	possibleMoves = {};
}

void LocalGame::processInput(const Input& input) {
	mouse = input.mousePos;

	if (input.mousePressed) {
		size_t i = 0;
		size_t j = 0;
		lookForMouseInBoard(i, j, getWhoFirst() == WhoGoesFirst::LEFT_FIRST);

		if (whoseTurnIsIt == Color::BLACK) {
			i = 7 - i;
			j = 7 - j;
		}

		if (i != 8 && j != 8) {
			Coord selected(i, j);
			if (game.getPieceAt(selected).color == whoseTurnIsIt) {
				selectedSquare.x = i;
				selectedSquare.y = j;

				possibleMoves = game.getMovesForPieceAt(selected);	
				pieceBeingHeld = game.getPieceAt(selected);
			}
		} else {
			possibleMoves.clear();
		}

	} else if (input.mouseReleased) {
		size_t i = 0;
		size_t j = 0;
		lookForMouseInBoard(i, j, getWhoFirst() == WhoGoesFirst::LEFT_FIRST);

		if (whoseTurnIsIt == Color::BLACK) {
			i = 7 - i;
			j = 7 - j;
		}

		if (i != 8 && j != 8) {
			Coord selected(i, j);
			if (possibleMoves.find(selected) != possibleMoves.end()) {
				//do stuff for making a move
				game.movePiece(selectedSquare, selected, false);
				previousMove.first = selectedSquare;
				previousMove.second = selected;

				whoseTurnIsIt = (whoseTurnIsIt == Color::WHITE) ? Color::BLACK : Color::WHITE;
				pieceBeingHeld = Piece();
				selectedSquare = Coord();
				possibleMoves.clear();

				//do a check to see if the game ended or promotion screen

			} else if (selected == selectedSquare) {
				pieceBeingHeld = Piece();
			} else {
				pieceBeingHeld = Piece();
				selectedSquare = Coord();
				possibleMoves.clear();
			}

		} else {
			pieceBeingHeld = Piece();
			selectedSquare = Coord();
			possibleMoves.clear();
		}
	}
}

void LocalGame::processRender(SDL_Renderer* renderer, const std::map<std::string, SDL_Texture*>& pieces) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_SetRenderScale(renderer, 1.0f, 1.0f);
	SDL_RenderClear(renderer);

	renderCheckeredBoard(leftBoard, renderer);
	renderCheckeredBoard(rightBoard, renderer);

	bool leftIsWhite = getWhoFirst() == WhoGoesFirst::LEFT_FIRST;

	//Highlights
	if (game.getIfInCheck()) {
		Coord king(game.getKingOf(whoseTurnIsIt));
		if (leftIsWhite) {
			renderHighlightAt(leftBoard[king.y][king.x], 255, 0, 0, renderer);
			renderHighlightAt(rightBoard[7 - king.y][7 - king.x], 255, 0, 0, renderer);
		} else {
			renderHighlightAt(rightBoard[king.y][king.x], 255, 0, 0, renderer);
			renderHighlightAt(leftBoard[7 - king.y][7 - king.x], 255, 0, 0, renderer);
		}
	}

	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			if (i == selectedSquare.x && j == selectedSquare.y) {
				if (leftIsWhite){
					renderHighlightAt(leftBoard[j][i], 0, 255, 0, renderer);
					renderHighlightAt(rightBoard[7 - j][7 - i], 0, 255, 0, renderer);
				} else {
					renderHighlightAt(rightBoard[j][i], 0, 255, 0, renderer);
					renderHighlightAt(leftBoard[7 - j][7 - i], 0, 255, 0, renderer);
				}
			}

			if ((i == previousMove.first.x && j == previousMove.first.y) 
					|| (i == previousMove.second.x && j == previousMove.second.y)) {
				if (leftIsWhite) {
					renderHighlightAt(leftBoard[j][i], 255, 255, 0, renderer);
					renderHighlightAt(rightBoard[7 - j][7 - i], 255, 255, 0, renderer);
				} else {
					renderHighlightAt(rightBoard[j][i], 255, 255, 0, renderer);
					renderHighlightAt(leftBoard[7 - j][7 - i], 255, 255, 0, renderer);
				}
			}

			for (const Coord square : possibleMoves) {
				if (i == square.x && j == square.y) {
					if (leftIsWhite) {
						renderHighlightAt(leftBoard[j][i], 0, 0, 255, renderer);
						renderHighlightAt(rightBoard[7 - j][7 - i], 0, 0, 255, renderer);
					} else {
						renderHighlightAt(rightBoard[j][i], 0, 0, 255, renderer);
						renderHighlightAt(leftBoard[7 - j][7 - i], 0, 0, 255, renderer);
					}
				}
			}

			//Pieces
			Piece currentPiece = game.getPieceAt(Coord(i, j));
			if (currentPiece.type != PieceType::NONE && ((i != selectedSquare.x || j != selectedSquare.y)
						|| pieceBeingHeld.type == PieceType::NONE)) {
				std::string key;
				key += static_cast<char>(currentPiece.color);
				key += static_cast<char>(currentPiece.type);

				if (leftIsWhite) {
					SDL_RenderTexture(renderer, pieces.at(key), NULL, &leftBoard[j][i]);
					SDL_RenderTexture(renderer, pieces.at(key), NULL, &rightBoard[7 - j][7 - i]);
				} else {
					SDL_RenderTexture(renderer, pieces.at(key), NULL, &leftBoard[7 - j][7 - i]);
					SDL_RenderTexture(renderer, pieces.at(key), NULL, &rightBoard[j][i]);
				}
			}
		}
	}

	//Held Piece
	if (pieceBeingHeld.type != PieceType::NONE) {
		SDL_FRect tempRect;
		tempRect.x = mouse.x - SQUARE_SIZE / 2;
		tempRect.y = mouse.y - SQUARE_SIZE / 2;
		tempRect.w = SQUARE_SIZE;
		tempRect.h = SQUARE_SIZE;

		std::string key;
		key += static_cast<char>(pieceBeingHeld.color);
		key += static_cast<char>(pieceBeingHeld.type);

		SDL_RenderTexture(renderer, pieces.at(key), NULL, &tempRect);
		SDL_RenderTexture(renderer, pieces.at(key), NULL, &tempRect);
	}

	SDL_RenderPresent(renderer);
}

void LocalGame::lookForMouseInBoard(size_t& i, size_t& j, bool leftIsWhite) {
	bool found = false;

	while (!found && i < 8) {
		while (!found && j < 8) {
			if (leftIsWhite) {
				if ((whoseTurnIsIt == Color::WHITE 
						&& SDL_PointInRectFloat(&mouse, &leftBoard[j][i]))
						|| (whoseTurnIsIt == Color::BLACK 
						&& SDL_PointInRectFloat(&mouse, &rightBoard[j][i]))) {
					found = true;
				} else {
					++j;
				}
			} else {
				if ((whoseTurnIsIt == Color::BLACK
						&& SDL_PointInRectFloat(&mouse, &leftBoard[j][i]))
						|| (whoseTurnIsIt == Color::WHITE
							&& SDL_PointInRectFloat(&mouse, &rightBoard[j][i]))) {
					found = true;
				} else {
					++j;
				}
			}
		}

		if (!found) {
			++i;
			j = 0;
		}
	}
}

void LocalGame::renderHighlightAt(const SDL_FRect& rect, const size_t r, const size_t g, 
		const size_t b, SDL_Renderer* renderer) const {
	SDL_FRect tempRect;
	tempRect.x = rect.x + SQUARE_SIZE / 6;
	tempRect.y = rect.y + SQUARE_SIZE / 6;
	tempRect.w = SQUARE_SIZE / 1.5;
	tempRect.h = SQUARE_SIZE / 1.5;

	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &tempRect);
}
