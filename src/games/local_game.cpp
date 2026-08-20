#include "local_game.h"

#include <iostream>

static const size_t WINDOW_WIDTH = 1730;
static const size_t WINDOW_HEIGHT = 1000;
static const size_t PADDING = 30;

LocalGame::LocalGame() {
	/*
	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			whitesBoard[i][j].x = PADDING + squareSize * i;
			whitesBoard[i][j].y = PADDING + squareSize * j;
			whitesBoard[i][j].w = squareSize;
			whitesBoard[i][j].h = squareSize;

			blacksBoard[i][j].x = WINDOW_WIDTH - 130 - squareSize * i;
			blacksBoard[i][j].y = WINDOW_HEIGHT - 270 - squareSize * j;
			blacksBoard[i][j].w = squareSize; 
			blacksBoard[i][j].h = squareSize;
		}
	}

	//promotionScreen
	inPromotionScreen = false;
	pieceBeingHeld = {};
	whoseTurnIsIt = Color::WHITE;
	previousMove = {};
	possibleMoves = {};
	*/
}

void LocalGame::processInput(const Input& input) {

}

void LocalGame::processRender(SDL_Renderer* renderer) {

}

/*
void LocalGame::run() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	renderBoardAt(PADDING, PADDING);
	renderBoardAt(WINDOW_HEIGHT - 100, PADDING);

	for (size_t i = 0; i < 8; ++i) {
		for (size_t j = 0; j < 8; ++j) {
			//Debug Map for squares
			//SDL_SetRenderDrawColor(renderer, i * 35, 0, j * 35, SDL_ALPHA_OPAQUE);	
			//SDL_RenderFillRect(renderer, &whitesBoard[i][j]);
			//SDL_RenderFillRect(renderer, &blacksBoard[i][j]);
			
			//Highlights
			if (i == selectedSquare.x && j == selectedSquare.y) {
				whoseTurnIsIt == Color::WHITE ? renderHighlightAt(whitesBoard[j][i], 0, 255, 0)
						: renderHighlightAt(blacksBoard[j][i], 0, 255, 0);
			}
			if ((i == previousMove.from.x && i == previousMove.from.x) 
					|| (i == previousMove.to.x && j == previousMove.to.x)) {
				whoseTurnIsIt == Color::WHITE ? renderHighlightAt(whitesBoard[j][i], 255, 255, 0)
						: renderHighlightAt(blacksBoard[j][i], 255, 255, 0);
			}
			for (const Coord square : possibleMoves) {
				if (i == square.x && j == square.y) {
					whoseTurnIsIt == Color::WHITE ? renderHighlightAt(whitesBoard[j][i], 0, 0, 255)
							: renderHighlightAt(blacksBoard[j][i], 0, 0, 255);
				}
			}

			//Pieces
			Piece currentPiece = board->getPieceAt(Coord(i, j));
			if (currentPiece.type != PieceType::NONE) {
				std::pair<Color, PieceType> key = {currentPiece.color, currentPiece.type};

				if (selectedSquare.x != i || selectedSquare.y != j 
						|| pieceBeingHeld.color != currentPiece.color) {
					SDL_RenderTexture(renderer, pieceTextures[key], NULL, &whitesBoard[j][i]);
					SDL_RenderTexture(renderer, pieceTextures[key], NULL, &blacksBoard[j][i]);
				} else {
					currentPiece.color == Color::BLACK
						? SDL_RenderTexture(renderer, pieceTextures[key], NULL, &whitesBoard[j][i])
						: SDL_RenderTexture(renderer, pieceTextures[key], NULL, &blacksBoard[j][i]);
				}
			}
		}
	}

	//Held Piece
	if (pieceBeingHeld.type != PieceType::NONE) {
		SDL_FRect tempRect;
		tempRect.x = mouseX - squareSize / 2;
		tempRect.y = mouseY - squareSize / 2;
		tempRect.w = squareSize;
		tempRect.h = squareSize;

		std::pair<Color, PieceType> key = {pieceBeingHeld.color, pieceBeingHeld.type};
		SDL_RenderTexture(renderer, pieceTextures[key], NULL, &tempRect);
		SDL_RenderTexture(renderer, pieceTextures[key], NULL, &tempRect);
	}

	//Selecting Squares
	Coord mouse = getCoordFromMouse();
	Color colorOfPieceThere = board->getPieceAt(mouse).color;
	bool mouseInWhitesBoard = mouseX < WINDOW_WIDTH / 2;
	if (mousePressed && whoseTurnIsIt == colorOfPieceThere 
			&& ((whoseTurnIsIt == Color::WHITE && mouseInWhitesBoard)
				|| whoseTurnIsIt == Color::BLACK && !mouseInWhitesBoard)) {

		selectedSquare = mouse;
		pieceBeingHeld = board->getPieceAt(selectedSquare);
		possibleMoves = board->getMovesForPieceAt(selectedSquare);

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
	tempRect.x = rect.x + squareSize / 6;
	tempRect.y = rect.y + squareSize / 6;
	tempRect.w = squareSize / 1.5;
	tempRect.h = squareSize / 1.5;

	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &tempRect);
}

Coord LocalGame::getCoordFromMouse() const {
	SDL_FPoint point = {mouseX, mouseY};
	size_t i = 0;
	size_t j = 0;
	bool found = false;
	while (!found && i < 8) {
		j = 0;
		while (!found && j < 8) {
			(SDL_PointInRectFloat(&point, &whitesBoard[j][i])
			 || SDL_PointInRectFloat(&point, &blacksBoard[j][i]))
				? found = true : ++j;
		}	
		if (!found) ++i;
	}
	
	return Coord(i, j);
}
*/
