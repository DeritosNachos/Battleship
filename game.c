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

//Returns 0 if player 1 starts, 1 if player 2 starts
int selectWhoStartsFirst(void) {
	return rand() % 2;
}

void manuallyPlaceShips(int carrierCoords[CARRIER_LENGTH*2], int battleshipCoords[BATTLESHIP_LENGTH*2],
	int submarineCoords[SUBMARINE_LENGTH*2], int cruiserCoords[CRUISER_LENGTH*2], int destroyerCoords[DESTROYER_LENGTH*2]) {
	int placing = 1, row = 0, col = 0;
	while (placing) {
		carrierPlacement:
		printf("Please enter the cells you would like to place the carrier in:\n");
		for (int i = 0; i < CARRIER_LENGTH; i++) {
			printf("Row #%d: ", i+1);
			scanf("%d", &row);
			printf("Col #%d: ", i+1);
			scanf("%d", &col);
			if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
				carrierCoords[i] = row;
				carrierCoords[i + 1] = col;
			}
		}
		if (checkPlacement(carrierCoords) == 0) {
			printf("That placement isn't valid! Please try again.\n");
			goto carrierPlacement;
		}
	}
}

int checkPlacement(int coords[]) {
	int isValid = 0, rowsValid = 0, colsValid = 0;
	int rowCheck = coords[0];
	int colCheck = coords[1];
	int size = sizeof(coords) / sizeof(int);
	for (int i = 0; i < size; i++) {
		//All indices 0, 2, 4, etc. are row #'s
		//All indices 1, 3, 5, etc. are col #'s
		if (i % 2 == 0) {
			//Row index
			if (coords[i] == rowCheck) {
				rowsValid = 1;
			} else {
				rowsValid = 0;
			}
		} else {
			//Column index
			if (coords[i] == colCheck) {
				colsValid = 1;
			} else {
				colsValid = 0;
			}
		}
	}
	if (rowsValid || colsValid) {
		return 1;
	}
	return 0;
}

