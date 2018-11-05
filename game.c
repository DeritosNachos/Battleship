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

void manuallyPlaceShips(char board[][NUM_COLS]) {
	int placing = 1, row = 0, col = 0;
	int carrierCoords[CARRIER_LENGTH * 2] = { 0 }, battleshipCoords[BATTLESHIP_LENGTH * 2] = { 0 },
		submarineCoords[SUBMARINE_LENGTH * 2] = { 0 }, cruiserCoords[CRUISER_LENGTH * 2] = { 0 }, destroyerCoords[DESTROYER_LENGTH * 2] = { 0 };
	while (placing) {
		carrierPlacement:
		printf("Please enter the cells you would like to place the carrier in:\n");
		int count = 0;
		for (int i = 0; i < (CARRIER_LENGTH*2); i+=2) {
			printf("Row #%d: ", ++count);
			scanf("%d", &row);
			printf("Col #%d: ", count);
			scanf("%d", &col);
			if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
				carrierCoords[i] = row;
				carrierCoords[i + 1] = col;
			}
			else {
				printf("Invalid row/column values!\n");
				goto carrierPlacement;
			}
		}
		if (checkPlacement(carrierCoords, CARRIER_LENGTH) == 0) {
			printf("That placement isn't valid! Please try again.\n");
			goto carrierPlacement;
		}
		//Carrier initialization/placement on board
		for (int i = 0; i < (CARRIER_LENGTH*2); i+=2) {
			board[carrierCoords[i]][carrierCoords[i+1]] = 'C';
		}
		break;

	battleshipPlacement:
		printf("Please enter the cells you would like to place the battleship in:\n");
		for (int i = 0; i < BATTLESHIP_LENGTH; i++) {
			printf("Row #%d: ", i + 1);
			scanf("%d", &row);
			printf("Col #%d: ", i + 1);
			scanf("%d", &col);
			if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
				battleshipCoords[i] = row;
				battleshipCoords[i + 1] = col;
			}
			else {
				printf("Invalid row/column values!\n");
				goto battleshipPlacement;
			}
		}
		if (checkPlacement(battleshipCoords, BATTLESHIP_LENGTH) == 0) {
			printf("That placement isn't valid! Please try again.\n");
			goto battleshipPlacement;
		}
		//Battleship initialization/placement on board
		for (int i = 0; i < (BATTLESHIP_LENGTH*2)+1; i+=2) {
			board[battleshipCoords[i]][battleshipCoords[i + 1]] = 'B';
		}

	submarinePlacement:
		printf("Please enter the cells you would like to place the carrier in:\n");
		for (int i = 0; i < SUBMARINE_LENGTH; i++) {
			printf("Row #%d: ", i + 1);
			scanf("%d", &row);
			printf("Col #%d: ", i + 1);
			scanf("%d", &col);
			if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
				submarineCoords[i] = row;
				submarineCoords[i + 1] = col;
			}
			else {
				printf("Invalid row/column values!\n");
				goto submarinePlacement;
			}
		}
		if (checkPlacement(submarineCoords, SUBMARINE_LENGTH) == 0) {
			printf("That placement isn't valid! Please try again.\n");
			goto submarinePlacement;
		}
		//Submarine initialization/placement on board
		for (int i = 0; i < (SUBMARINE_LENGTH*2)+1; i+=2) {
			board[submarineCoords[i]][submarineCoords[i+1]] = 'S';
		}

	cruiserPlacement:
		printf("Please enter the cells you would like to place the carrier in:\n");
		for (int i = 0; i < CRUISER_LENGTH; i++) {
			printf("Row #%d: ", i + 1);
			scanf("%d", &row);
			printf("Col #%d: ", i + 1);
			scanf("%d", &col);
			if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
				cruiserCoords[i] = row;
				cruiserCoords[i + 1] = col;
			}
			else {
				printf("Invalid row/column values!\n");
				goto cruiserPlacement;
			}
		}
		if (checkPlacement(carrierCoords, CRUISER_LENGTH) == 0) {
			printf("That placement isn't valid! Please try again.\n");
			goto cruiserPlacement;
		}
		//Cruiser initialization/placement on board
		for (int i = 0; i < (CRUISER_LENGTH*2)+1; i+=2) {
			board[cruiserCoords[i]][cruiserCoords[i+1]] = 'R';
		}

	destroyerPlacement:
		printf("Please enter the cells you would like to place the carrier in:\n");
		for (int i = 0; i < DESTROYER_LENGTH; i++) {
			printf("Row #%d: ", i + 1);
			scanf("%d", &row);
			printf("Col #%d: ", i + 1);
			scanf("%d", &col);
			if ((row >= 0 && row <= 9) && (col >= 0 && col <= 9)) {
				destroyerCoords[i] = row;
				destroyerCoords[i + 1] = col;
			}
			else {
				printf("Invalid row/column values!\n");
				goto destroyerPlacement;
			}
		}
		if (checkPlacement(carrierCoords, DESTROYER_LENGTH) == 0) {
			printf("That placement isn't valid! Please try again.\n");
			goto destroyerPlacement;
		}
		//Destroyer initialization/placement on board
		for (int i = 0; i < (DESTROYER_LENGTH*2)+1; i+=2) {
			board[destroyerCoords[i]][destroyerCoords[i+1]] = 'C';
		}
	}
}

//Add board checking
int checkPlacement(int coords[], int shipSize) {
	int rowsValid = 1, colsValid = 1;
	int rowCheck = coords[0];
	int colCheck = coords[1];
	int size = sizeof(coords) / sizeof(int);
	int rowCoords[100] = { 0 };
	int colCoords[100] = { 0 };
	int count = 0;
	//Row checking
	for (int i = 0; i < shipSize*2; i += 2) {
		rowCoords[count] = coords[i];
		if (coords[i] != rowCheck) {
			rowsValid = 0;
		}
		count++;
	}

	//Column checking
	count = 0;
	for (int i = 1; i < shipSize*2; i += 2) {
		colCoords[count] = coords[i];
		if (coords[i] != colCheck) {
			colsValid = 0;
		}
		count++;
	}

	if ((rowsValid && !colsValid)) {
		//Check column values are in sequence by sorting
		bubbleSort(colCoords, shipSize);
		for (int i = 1; i < shipSize; i++) {
			if (colCoords[i] > colCoords[i - 1] + 1) {
				return 0;
			}
		}
		return 1;
	}
	else if ((!rowsValid && colsValid)) {
		//Check row values are in sequence by sorting
		bubbleSort(rowCoords, shipSize);
		for (int i = 1; i < shipSize; i++) {
			if (rowCoords[i] > rowCoords[i - 1] + 1) {
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

//Implemented bubble sort for use in other functions
void bubbleSort(int arr[], int size) {
	int temp = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

