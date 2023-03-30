import java.io.File;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;


public class BattleshipGame {

    public static void main(String[] args) {
        Random rand = new Random();

        GameFunctions game = new GameFunctions();

        //Note that playerTwoBoard mostly exists for debugging purposes.
        //Variable instantiation. Bool and int mixed types due to function implementation.
        char[][] playerOneBoard = new char[GameFunctions.NUM_ROWS][GameFunctions.NUM_COLS];
        char[][] playerTwoBoard = new char[GameFunctions.NUM_ROWS][GameFunctions.NUM_COLS];
                char[][] pTwoShownBoard = new char[GameFunctions.NUM_ROWS][GameFunctions.NUM_COLS];
                char[] shipSymbols = { 'C', 'B', 'S', 'R', 'D' };
        int[][] computerHasTried = new int[GameFunctions.NUM_ROWS][GameFunctions.NUM_COLS];
        int[] shipLengths = { GameFunctions.CARRIER_LENGTH, GameFunctions.BATTLESHIP_LENGTH, GameFunctions.SUBMARINE_LENGTH, GameFunctions.CRUISER_LENGTH, GameFunctions.DESTROYER_LENGTH };
        int direction = GameFunctions.HORIZONTAL, rowStart = 0, colStart = 0;
        int intIn = 0, xPos = 0, yPos = 0, wasHit = 0, wasSunk = 0, generating = 1;
        boolean placing = false, hasWon = false, hasLost = false;
        char shipHit = '\0';
        double[] playerOne = {0, 0, 0, 0.0};
        double[] playerTwo = {0, 0, 0, 0.0};
        File output = new File("battleship.log");

        GameFunctions.initializeBoard(playerOneBoard, GameFunctions.NUM_ROWS, GameFunctions.NUM_COLS);
        GameFunctions.initializeBoard(playerTwoBoard, GameFunctions.NUM_ROWS, GameFunctions.NUM_COLS);
        GameFunctions.initializeBoard(pTwoShownBoard, GameFunctions.NUM_ROWS, GameFunctions.NUM_COLS);

        //ASCII art generated at http://patorjk.com/software/taag/.
        System.out.print(" ____    ____  ______  ______  _        ___  _____ __ __  ____  ____  \n");
        System.out.print("|    \\  /    ||      ||      || |      /  _]/ ___/|  |  ||    ||    \\ \n");
        System.out.print("|  o  )|  o  ||      ||      || |     /  [_(   \\_ |  |  | |  | |  o  )\n");
        System.out.print("|     ||     ||_|  |_||_|  |_|| |___ |    _]\\__  ||  _  | |  | |   _/ \n");
        System.out.print("|  O  ||  _  |  |  |    |  |  |     ||   [_ /  \\ ||  |  | |  | |  |   \n");
        System.out.print("|     ||  |  |  |  |    |  |  |     ||     |\\    ||  |  | |  | |  |   \n");
        System.out.print("|_____||__|__|  |__|    |__|  |_____||_____| \\___||__|__||____||__|   \n");
        System.out.print("          implemented by Zach Nett/Refactored to Java By Derik Nguyen\n\n");
        System.out.print("1. This is a multiplayer, two player game.\n");
        System.out.print("2. Player 1 is you, Player 2 is the computer.\n");
        System.out.print("3. You and your opponent have five ships each: a carrier, battleship, submarine,\n");
        System.out.print("   cruiser, and destroyer. Your objective is to guess your enemy's ships' coordinates.\n");
        System.out.print("   If you manage to 'sink' (destroy all of your enemy's ships), you win!\n");
        System.out.print("Press enter to start the game!\n");
        Scanner newScanner = new Scanner(System.in);
        newScanner.nextLine();

        GameFunctions.clearScreen();
        //Manual or random placement
        System.out.print("Would you like to manually place your ships, or randomly generate a board?\n");
        System.out.print("1. Randomly generate board.\n");
        System.out.print("2. Manually place ships.\n");
        do {
            intIn = Integer.parseInt(newScanner.nextLine());
        } while (!(intIn == 1 || intIn == 2));
        if (intIn == 1) {
            for (int i = 0; i < 5; i++) {
                //Random placement of ships for player (Player 1)
                placing = true;
                direction = GameFunctions.generateDirection();
                do {
                    generateStartingPoint(direction, shipLengths[i], rowStart, colStart);
                    if (detectCollision(playerOneBoard, direction, shipLengths[i], rowStart, colStart) == 1) {
                        placeShip(playerOneBoard, NUM_ROWS, NUM_COLS, shipLengths[i], shipSymbols[i], direction, rowStart, colStart);
                        placing = false;
                    }
                } while (placing);
            }
        } else {
            manuallyPlaceShips(playerOneBoard);
        }
        System.out.print("YOUR BOARD:\n");
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
            System.out.print("Player 1 has been randomly selected to go first.\n");
        }
        else if (currentPlayer == 1) { //Computer
            System.out.print("Player 2 (computer) has been randomly selected to go first.\n");
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
                    System.out.print("Your Board:\n");
                    printBoard(playerOneBoard, NUM_ROWS, NUM_COLS);
                    System.out.print("\nComputer's Board:\n");
                    printBoard(pTwoShownBoard, NUM_ROWS, NUM_COLS);
                    System.out.print("Enter a target: ");
                    newScanner.nextLine("%d %d", &xPos, &yPos);
                    playerOne.totalShots++;
                    wasHit = checkShot(playerTwoBoard, xPos, yPos, &shipHit);
                    wasSunk = checkIfSunkShip(playerTwoBoard, shipHit);
                    updateBoard(playerTwoBoard, xPos, yPos, wasHit);
                    updateBoard(pTwoShownBoard, xPos, yPos, wasHit);
                    if (wasHit) {
                        playerOne.numHits++;
                        System.out.print("Hit!\n");
                        if (wasSunk) {
                            System.out.print("You sunk the computer's ship with token %c!\n", shipHit);
                        }
                    } else {
                        playerOne.numMisses++;
                        System.out.print("Miss...\n");
                    }
                    system("pause");
                    system("cls");
                    outputCurrentMove(outfile, currentPlayer, xPos, yPos, wasHit, wasSunk);
                    if (isWinner(playerTwoBoard)) {
                        System.out.print("You won!\n");
                        system("pause");
                        hasWon = 1;
				goto breakout;
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
                        System.out.print("Computer selects %d, %d. It was a hit!\n", xPos, yPos);
                        if (wasSunk) {
                            System.out.print("Computer selects %d, %d. It was a hit and sunk your ship!\n", xPos, yPos);
                        }
                    } else {
                        playerTwo.numMisses++;
                        System.out.print("Computer selects %d, %d. It was a miss.\n", xPos, yPos);
                    }
                    system("pause");
                    system("cls");
                    updateBoard(playerOneBoard, xPos, yPos, wasHit);
                    if (isWinner(playerOneBoard)) {
                        System.out.print("You lost!\n");
                        system("pause");
                        hasLost = 1;
				goto breakout;
                    }
                    outputCurrentMove(outfile, currentPlayer, xPos, yPos, wasHit, wasSunk);
                    currentPlayer = 0;
                    break;
            }
        }

        breakout:
        System.out.print("Printing statistics to battleship.log...\n");
        playerOne.hitsMisses = ((double) playerOne.numHits / playerOne.totalShots)*100;
        playerTwo.hitsMisses = ((double)playerTwo.numHits / playerTwo.totalShots)*100;
        outputStats(outfile, playerOne, playerTwo);
        fclose(outfile);

        return 0; //End of main function
}
