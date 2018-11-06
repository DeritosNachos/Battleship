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

	initializeBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
	initializeBoard(playerTwoBoard, NUM_ROWS, NUM_COLS);
	initializeBoard(pTwoShownBoard, NUM_ROWS, NUM_COLS);
	printf("Welcome to BATTLESHIP!\n");
	printf("1. This is a two player game.\n");
	printf("2. Player 1 is you, player 2 is the computer.\n");
	printf("Press enter to start the game!\n");
	getch();
	system("cls");
	//Manual or random placement
	printf("Would you like to manually place your ships, or randomly generate a board?\n");
	printf("1. Randomly generate board.\n");
	printf("2. Manually place ships.\n");
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
				if (detectCollision(playerOneBoard, direction, shipLengths[i], rowStart, colStart) == 1) {
					placeShip(playerOneBoard, NUM_ROWS, NUM_COLS, shipLengths[i], shipSymbols[i], direction, rowStart, colStart);
					placing = false;
				}
			} while (placing);
		}
	} else {
		manuallyPlaceShips(playerOneBoard);
	}
	printf("YOUR BOARD:\n");
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

	int currentPlayer = selectWhoStartsFirst();
	if (currentPlayer == 0) { //Player
		printf("Player 1 has been randomly selected to go first.\n");
	}
	else if (currentPlayer == 1) { //Computer
		printf("Player 2 (computer) has been randomly selected to go first.\n");
	}
	system("pause");
	system("cls");
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
			printBoard(playerTwoBoard, NUM_ROWS, NUM_COLS);
			printf("Enter a target: ");
			scanf("%d %d", &xPos, &yPos);
			playerOne.totalShots++;
			wasHit = checkShot(playerTwoBoard, xPos, yPos, &shipHit);
			wasSunk = checkIfSunkShip(playerTwoBoard, shipHit);
			updateBoard(playerTwoBoard, xPos, yPos, wasHit);
			updateBoard(pTwoShownBoard, xPos, yPos, wasHit);
			if (wasHit) {
				playerOne.numHits++;
				printf("Hit!\n");
				if (wasSunk) {
					printf("You sunk the computer's ship with token %c!\n", shipHit);
				}
			} else {
				playerOne.numMisses++;
				printf("Miss...\n");
			}
			system("pause");
			system("cls");
			outputCurrentMove(outfile, currentPlayer, xPos, yPos, wasHit, wasSunk);
			if (isWinner(playerTwoBoard)) {
				printf("You won!\n");
				system("pause");
				hasWon = 1;
				currentPlayer = 2;
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
			playerTwo.totalShots++;
			wasHit = checkShot(playerOneBoard, xPos, yPos, &shipHit);
			wasSunk = checkIfSunkShip(playerOneBoard, shipHit);
			if (wasHit) {
				playerTwo.numHits++;
				printf("Computer selects %d, %d. It was a hit!\n", xPos, yPos);
				if (wasSunk) {
					printf("Computer selects %d, %d. It was a hit and sunk your ship!\n", xPos, yPos);
				}
			} else {
				playerTwo.numMisses++;
				printf("Computer selects %d, %d. It was a miss.\n", xPos, yPos);
			}
			system("pause");
			system("cls");
			updateBoard(playerOneBoard, xPos, yPos, wasHit);
			if (isWinner(playerOneBoard)) {
				printf("You lost!\n");
				system("pause");
				hasLost = 1;
				currentPlayer = 2;
				break;
			}
			outputCurrentMove(outfile, currentPlayer, xPos, yPos, wasHit, wasSunk);
			currentPlayer = 0;
			break;
		case 2:
			//Breakout case.
			printf("Printing statistics to battleship.log...\n");
		}
	}
	playerOne.hitsMisses = (double) playerOne.numHits / playerOne.numMisses;
	playerTwo.hitsMisses = (double)playerTwo.numHits / playerTwo.numMisses;
	outputStats(outfile, playerOne, playerTwo);
	fclose(outfile);

	return 0; //End of main function
}