#include "game.h"

int main(void) {
	srand((unsigned int) time(NULL));

	char playerOneBoard[10][10] = { {'\0'} },
		shipSymbols[5] = { 'C', 'B', 'S', 'R', 'D' };
	int shipLengths[5] = { CARRIER_LENGTH, BATTLESHIP_LENGTH, SUBMARINE_LENGTH, CRUISER_LENGTH, DESTROYER_LENGTH };
	int direction = 0, rowStart = 0, colStart = 0;

	initializeBoard(playerOneBoard, 10, 10);
	printBoard(playerOneBoard, 10, 10);
	printf("\n\n");
	for (int i = 0; i < 5; i++) {
		direction = generateDirection();
		generateStartingPoint(direction, shipLengths[i], &rowStart, &colStart);
		placeShip(playerOneBoard, NUM_ROWS, NUM_COLS, shipLengths[i], shipSymbols[i], direction, rowStart, colStart);
		printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
		printf("\n\n");
	}

	return 0; //End of main function
}