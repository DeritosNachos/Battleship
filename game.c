#include "game.h"

void initializeBoard(char board[10][10], int numRows, int numColumns) {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			board[i][j] = '~';
		}
	}
}

void printBoard(char board[10][10], int numRows, int numColumns) {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numColumns; j++) {
			printf(" %c ", board[i][j]);
		}
		printf("\n");
	}
}

int generateDirection(void) {
	return rand() % 2;
}

void generateStartingPoint(int direction, int shipLength, int *row, int *column) {
	if (direction == HORIZONTAL) {
		*row = rand() % NUM_ROWS;
		*column = rand() % (NUM_COLS - shipLength + 1);
	} else if (direction == VERTICAL) {
		*column = rand() % NUM_COLS;
		*row = rand() % (NUM_ROWS - shipLength + 1);
	}
}

void placeShip(char board[][NUM_COLS], int numRows, int numCols, int shipLength, char shipSymbol, int direction, int rowStart, int colStart) {
	if (direction == HORIZONTAL) {
		for (int i = 0; i < shipLength; i++) {
			board[rowStart][colStart + i] = shipSymbol;
		}
	} else if (direction == VERTICAL) {
		for (int i = 0; i < shipLength; i++) {
			board[rowStart + i][colStart] = shipSymbol;
		}
	}
}

int detectCollision(char board[][NUM_COLS], int direction, int shipLength, int row, int col) {
	int isValid = 0;
	if (direction == HORIZONTAL) {
		for (int i = 0; i < shipLength; i++) {
			if (board[row][col+i] != '~') {
				isValid = 0;
			} else {
				isValid = 1;
			}
		}
	}
	else if (direction == VERTICAL) {
		for (int i = 0; i < shipLength; i++) {
			if (board[row + i][col] != '~') {
				isValid = 0;
			}
			else {
				isValid = 1;
			}
		}
	}
	
	return isValid;
}