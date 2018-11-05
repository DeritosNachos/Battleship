#include "game.h"

int main(void) {
	srand((unsigned int)time(NULL));

	char playerOneBoard[NUM_ROWS][NUM_COLS] = { {'\0'} },
		playerTwoBoard[NUM_ROWS][NUM_COLS] = { { '\0'} },
		shipSymbols[5] = { 'C', 'B', 'S', 'R', 'D' };
	int playerOneHits[NUM_ROWS][NUM_COLS] = { { 0 } },
		playerTwoHits[NUM_ROWS][NUM_COLS] = { { 0 } };
	int shipLengths[5] = { CARRIER_LENGTH, BATTLESHIP_LENGTH, SUBMARINE_LENGTH, CRUISER_LENGTH, DESTROYER_LENGTH };
	int direction = HORIZONTAL, rowStart = 0, colStart = 0;
	int intIn = 0;
	bool placing = false;

	//Ship carrier = { CARRIER_LENGTH, 0, 'C' }, battleship = { BATTLESHIP_LENGTH, 0, 'B' },
	//	 submarine = { SUBMARINE_LENGTH, 0, 'S' }, cruiser = { CRUISER_LENGTH, 0, 'R' },
	//	 destroyer = { DESTROYER_LENGTH, 0, 'D' };

	initializeBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
	initializeBoard(playerTwoBoard, NUM_ROWS, NUM_COLS);
	printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
	printf("\n\n");

	//Manual or random placement
	printf("Would you like to manually place your ships, or randomly generate a board?\n");
	printf("1. Randomly generate\n");
	printf("2. Manually place\n");
	do {
		scanf("%d", &intIn);
	} while (!(intIn == 1 || intIn == 2));
	if (intIn == 1) {
		for (int i = 0; i < 5; i++) {
			//Random placement of ships for player (Player 1)
			placing = true;
			direction = generateDirection();
			do {
				generateStartingPoint(direction, shipLengths[i], &rowStart, &colStart);
				if (detectCollision(playerOneBoard, direction, shipLengths[i], rowStart, colStart) == true) {
					placeShip(playerOneBoard, NUM_ROWS, NUM_COLS, shipLengths[i], shipSymbols[i], direction, rowStart, colStart);
					placing = false;
				}
			} while (placing);
		}
	} else {
		manuallyPlaceShips(playerOneBoard);
	}
	printf("PLAYER ONE BOARD:\n");
	printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
	system("pause");

	for (int i = 0; i < 5; i++) {
		//Random placement of ships for computer (Player 2)
		placing = true;
		direction = generateDirection();
		do {
			generateStartingPoint(direction, shipLengths[i], &rowStart, &colStart);
			if (detectCollision(playerTwoBoard, direction, shipLengths[i], rowStart, colStart) == true) {
				placeShip(playerTwoBoard, NUM_ROWS, NUM_COLS, shipLengths[i], shipSymbols[i], direction, rowStart, colStart);
				placing = false;
			}
		} while (placing);
	}
	printf("PLAYER 2 BOARD:\n");
	printBoard(playerTwoBoard, NUM_ROWS, NUM_COLS);

	return 0; //End of main function
}