#include "game.h"

int main(void) {
	srand((unsigned int)time(NULL));

	char playerOneBoard[NUM_ROWS][NUM_COLS] = { {'\0'} },
		playerTwoBoard[NUM_ROWS][NUM_COLS] = { { '\0'} },
		pTwoShownBoard[NUM_ROWS][NUM_COLS] = { { '\0' } },
		shipSymbols[5] = { 'C', 'B', 'S', 'R', 'D' };
	int computerHasTried[NUM_ROWS][NUM_COLS] = { { 0 } };
	int shipLengths[5] = { CARRIER_LENGTH, BATTLESHIP_LENGTH, SUBMARINE_LENGTH, CRUISER_LENGTH, DESTROYER_LENGTH };
	int direction = HORIZONTAL, rowStart = 0, colStart = 0;
	int intIn = 0, xPos = 0, yPos = 0, wasHit = 0, wasSunk = 0, generating = 1;
	bool placing = false, hasWon = false, hasLost = false;
	char shipHit = '\0';
	Stats playerOne = {0, 0, 0, 0.0};
	Stats playerTwo = {0, 0, 0, 0.0};

	FILE *outfile = NULL;
	outfile = fopen("battleship.log", "w");

	//Ship carrier = { CARRIER_LENGTH, 0, 'C' }, battleship = { BATTLESHIP_LENGTH, 0, 'B' },
	//	 submarine = { SUBMARINE_LENGTH, 0, 'S' }, cruiser = { CRUISER_LENGTH, 0, 'R' },
	//	 destroyer = { DESTROYER_LENGTH, 0, 'D' };

	initializeBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
	initializeBoard(playerTwoBoard, NUM_ROWS, NUM_COLS);
	initializeBoard(pTwoShownBoard, NUM_ROWS, NUM_COLS);
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
	printBoard(pTwoShownBoard, NUM_ROWS, NUM_COLS);

	int currentPlayer = selectWhoStartsFirst();
	if (currentPlayer == 0) { //Player
		printf("Player 1 has been randomly selected to go first.\n");
	}
	else if (currentPlayer == 1) { //Computer
		printf("Player 2 (computer) has been randomly selected to go first.\n");
	}

	//Initialize computer parallel array
	for (int i = 0; i < NUM_ROWS; i++) {
		for (int j = 0; j < NUM_COLS; j++) {
			computerHasTried[i][j] = 0;
		}
	}

	while (!hasWon || !hasLost) {
		switch (currentPlayer) {
		case 0: //Player
			printf("Your Board:\n");
			printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
			printf("\nComputer's Board:\n");
			printBoard(pTwoShownBoard, NUM_ROWS, NUM_COLS);
			printf("Enter a target: ");
			scanf("%d %d", &xPos, &yPos);
			updateBoard(playerTwoBoard, xPos, yPos);
			updateBoard(pTwoShownBoard, xPos, yPos);
			wasHit = checkShot(playerTwoBoard, xPos, yPos, &shipHit);
			wasSunk = checkIfSunkShip(playerTwoBoard, shipHit);

			outputCurrentMove(outfile, currentPlayer, xPos, yPos, wasHit, wasSunk);
			if (isWinner(playerTwoBoard)) {
				printf("You won!\n");
				hasWon = 1;
				break;
			}
			currentPlayer = 1;
			break;
		case 1: //Computer
			generating = 1;
			while (generating) {
				xPos = rand() % 10;
				yPos = rand() % 10;
				if (computerHasTried[xPos][yPos] != 1) {
					computerHasTried[xPos][yPos] = 1;
					generating = 0;
				}
			}
			updateBoard(playerOneBoard, xPos, yPos);
			wasHit = checkShot(playerOneBoard, xPos, yPos, &shipHit);
			wasSunk = checkIfSunkShip(playerOneBoard, shipHit);
			if (isWinner(playerOneBoard)) {
				printf("You lost!\n");
				hasLost = 1;
				break;
			}
			outputCurrentMove(outfile, currentPlayer, xPos, yPos, wasHit, wasSunk);
			currentPlayer = 0;
			break;
		}
	}
	outputStats(outfile, playerOne, playerTwo);
	fclose(outfile);

	return 0; //End of main function
}