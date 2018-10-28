#include "game.h"

int main(void) {
	srand((unsigned int)time(NULL));

	char playerOneBoard[10][10] = { {'\0'} },
		shipSymbols[5] = { 'C', 'B', 'S', 'R', 'D' };
	int shipLengths[5] = { CARRIER_LENGTH, BATTLESHIP_LENGTH, SUBMARINE_LENGTH, CRUISER_LENGTH, DESTROYER_LENGTH };
	int direction = 0, rowStart = 0, colStart = 0, placing = 0;

	Ship carrier = { CARRIER_LENGTH, 0, 'C' }, battleship = { BATTLESHIP_LENGTH, 0, 'B' },
		 submarine = { SUBMARINE_LENGTH, 0, 'S' }, cruiser = { CRUISER_LENGTH, 0, 'R' },
		 destroyer = { DESTROYER_LENGTH, 0, 'D' };

	initializeBoard(playerOneBoard, 10, 10);
	printBoard(playerOneBoard, 10, 10);
	printf("\n\n");

	for (int i = 0; i < 5; i++) {
		placing = 1;
		direction = generateDirection();
		do {
			generateStartingPoint(direction, shipLengths[i], &rowStart, &colStart);
			if (detectCollision(playerOneBoard, direction, shipLengths[i], rowStart, colStart) == 1) {
				placeShip(playerOneBoard, NUM_ROWS, NUM_COLS, shipLengths[i], shipSymbols[i], direction, rowStart, colStart);
				placing = 0;
			}
		} while (placing);
	}
	printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);

	return 0; //End of main function
}