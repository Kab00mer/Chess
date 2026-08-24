#include "local_game.h"

#include <iostream>

static const size_t WINDOW_WIDTH = 640;
static const size_t WINDOW_HEIGHT = 360;
static const size_t PADDING = 5;
static const size_t SQUARE_SIZE = 18;
static const size_t CENTER_PADDING = 22;

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

}

void LocalGame::processRender(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	renderBoardAt(leftBoard, renderer);
	renderBoardAt(rightBoard, renderer);

	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			//Debug Map for squares
			//SDL_SetRenderDrawColor(renderer, i * 35, 0, j * 35, SDL_ALPHA_OPAQUE);	
			//SDL_RenderFillRect(renderer, &leftBoard[i][j]);
			//SDL_RenderFillRect(renderer, &rightBoard[i][j]);
			
			//Highlights
			if (i == selectedSquare.x && j == selectedSquare.y) {
				whoseTurnIsIt == Color::WHITE ? renderHighlightAt(leftBoard[j][i], 0, 255, 0)
						: renderHighlightAt(rightBoard[j][i], 0, 255, 0);
			}
			if ((i == previousMove.from.x && i == previousMove.from.x) 
					|| (i == previousMove.to.x && j == previousMove.to.x)) {
				whoseTurnIsIt == Color::WHITE ? renderHighlightAt(leftBoard[j][i], 255, 255, 0)
						: renderHighlightAt(rightBoard[j][i], 255, 255, 0);
			}
			for (const Coord square : possibleMoves) {
				if (i == square.x && j == square.y) {
					whoseTurnIsIt == Color::WHITE ? renderHighlightAt(leftBoard[j][i], 0, 0, 255)
							: renderHighlightAt(rightBoard[j][i], 0, 0, 255);
				}
			}

			//Pieces
			Piece currentPiece = board.getPieceAt(Coord(i, j));
			if (currentPiece.type != PieceType::NONE) {
				std::pair<Color, PieceType> key = {currentPiece.color, currentPiece.type};

				if (selectedSquare.x != i || selectedSquare.y != j 
						|| pieceBeingHeld.color != currentPiece.color) {
					SDL_RenderTexture(renderer, pieceTextures[key], NULL, &leftBoard[j][i]);
					SDL_RenderTexture(renderer, pieceTextures[key], NULL, &rightBoard[j][i]);
				} else {
					currentPiece.color == Color::BLACK
						? SDL_RenderTexture(renderer, pieceTextures[key], NULL, &leftBoard[j][i])
						: SDL_RenderTexture(renderer, pieceTextures[key], NULL, &rightBoard[j][i]);
				}
			}
		}
	}

	//Held Piece
	if (pieceBeingHeld.type != PieceType::NONE) {
		SDL_FRect tempRect;
		tempRect.x = input.mouseX - SQUARE_SIZE / 2;
		tempRect.y = input.mouseY - SQUARE_SIZE / 2;
		tempRect.w = SQUARE_SIZE;
		tempRect.h = SQUARE_SIZE;

		std::pair<Color, PieceType> key = {pieceBeingHeld.color, pieceBeingHeld.type};
		SDL_RenderTexture(renderer, pieceTextures[key], NULL, &tempRect);
		SDL_RenderTexture(renderer, pieceTextures[key], NULL, &tempRect);
	}

	//Selecting Squares
	Coord mouse = getCoordFromMouse(input);
	Color colorOfPieceThere = board.getPieceAt(mouse).color;
	bool mouseInWhitesBoard = mouseX < WINDOW_WIDTH / 2;
	if (mousePressed && whoseTurnIsIt == colorOfPieceThere 
			&& ((whoseTurnIsIt == Color::WHITE && mouseInWhitesBoard)
				|| whoseTurnIsIt == Color::BLACK && !mouseInWhitesBoard)) {

		selectedSquare = mouse;
		pieceBeingHeld = board.getPieceAt(selectedSquare);
		possibleMoves = board.getMovesForPieceAt(selectedSquare);

	} else if (mouseReleased) {
		if (i == selectedSquare.x && j == selectedSquare.y) {
			pieceBeingHeld = Piece();
		} else if (false) {

		} else {
			selectedSquare = Coord();
			pieceBeingHeld = Piece();
			possibleMoves.clear(); 
		}
	}

	SDL_RenderPresent(renderer);
}

void LocalGame::renderHighlightAt(const SDL_FRect& rect, const size_t r, const size_t g, const size_t b) const {
	SDL_FRect tempRect;
	tempRect.x = rect.x + SQUARE_SIZE / 6;
	tempRect.y = rect.y + SQUARE_SIZE / 6;
	tempRect.w = SQUARE_SIZE / 1.5;
	tempRect.h = SQUARE_SIZE / 1.5;

	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &tempRect);
}

Coord LocalGame::getCoordFromMouse(const Input& input) const {
	SDL_FPoint point = {input.mouseX, input.mouseY};
	size_t i = 0;
	size_t j = 0;
	bool found = false;
	while (!found && i < 8) {
		j = 0;
		while (!found && j < 8) {
			(SDL_PointInRectFloat(&point, &leftBoard[j][i])
			 || SDL_PointInRectFloat(&point, &rightBoard[j][i]))
				? found = true : ++j;
		}	
		if (!found) ++i;
	}
	
	return Coord(i, j);
}
