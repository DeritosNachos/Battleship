import java.util.Random;

public class GameFunctions {


    public static int HORIZONTAL = 0;
    public static int VERTICAL   = 1;
    public static int NUM_ROWS = 10;
    public static int NUM_COLS = 10;
    public static int CARRIER_LENGTH = 5;
    public static int BATTLESHIP_LENGTH = 4;
    public static int SUBMARINE_LENGTH = 3;
    public static int CRUISER_LENGTH = 3;
    public static int DESTROYER_LENGTH = 2;
    Random rand = new Random();

    //function to clear screen
    public static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    //Function initializeBoard, parameters 2D array of characters and integers.
//Initializes all values on provided game board to ~ to represent water.
    public static void initializeBoard(char board[][], int numRows, int numColumns) {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numColumns; j++) {
                board[i][j] = '~';
            }
        }
    }

    //Function printBoard, parameters 2D array of characters and integers.
//Prints 2D array character by character, with index markings on the left and top.
    public static void printBoard(char board[][], int numRows, int numColumns) {
        for (int i = 0; i < numRows; i++) {
            if (i == 0) {
                System.out.println("    0  1  2  3  4  5  6  7  8  9\n");
            }
            for (int j = 0; j < numColumns; j++) {
                if (j == 0) {
                    System.out.printf(" %d ", i);
                }
                System.out.printf(" %c ", board[i][j]);
            }
            System.out.print("\n");
        }
    }

    //Function generateDirection.
//Generates a random number 0-1, 0 being horizontal, 1 vertical, returns it.
    public static int generateDirection() {
        Random randomNumber = new Random();
        int number = randomNumber.nextInt(100) % 2;
        return number;
    }

    //Function generateStartingPoint, parameters integers and integer pointers.
//Generates a starting point for a ship based on ship length and direction.
    void generateStartingPoint(int direction, int shipLength, int row, int column) {
        if (direction == HORIZONTAL) {
		row = rand.nextInt() % NUM_ROWS;
		column = rand.nextInt() % (NUM_COLS - shipLength + 1);
        } else if (direction == VERTICAL) {
		column = rand.nextInt() % NUM_COLS;
		row = rand.nextInt() % (NUM_ROWS - shipLength + 1);
        }
    }

    //Function placeShip, parameters 2D array of characters, various integers (starting point, length of ship, etc.), character for ship symbol.
//Places the ship onto the board based on provided starting point, length, direction, and symbol.
    void placeShip(char[][] board, int numRows, int numCols, int shipLength, char shipSymbol, int direction, int rowStart, int colStart) {
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

    //Function detectCollision, parameters 2D array of characters, integers (direction, length of ship, row and column).
//Detects if placement of ship is invalid (that is, if the placement of the ship given length and direction would intersect something other than water.)
//Returns 1 if valid placement, 0 if not.
    int detectCollision(char[][] board, int direction, int shipLength, int row, int col) {
        int isValid = 0;
        if (direction == HORIZONTAL) {
            for (int i = 0; i < shipLength; i++) {
                if (board[row][col+i] != '~') {
                    isValid = 0;
                } else if (board[row][col + 1] == '~') {
                    isValid = 1;
                }
            }
        }
        else if (direction == VERTICAL) {
            for (int i = 0; i < shipLength; i++) {
                if (board[row + i][col] != '~') {
                    isValid = 0;
                }
                else if (board[row + i][col] == '~') {
                    isValid = 1;
                }
            }
        }
        return isValid;
    }

    //Function selectWhoStartsFirst.
//Returns 0 if player 1 starts, 1 if player 2 (computer) starts.
    int selectWhoStartsFirst(void) {
        return rand.nextInt() % 2;
    }

    //Function manuallyPlaceShips, parameter 2D array of characters.
//Prompts user for individual coordinates for every ship. If they are valid values, the board is initialized with the respective ship's token
//on the parameter board (2D character array).
//Iterates by 2 based on coordinates (even indices in arrays are row numbers, odd indices are column numbers).
//Note that this coordinate array format is a prerequisite for this function's sister function, checkPlacement.
    void manuallyPlaceShips(char[][] board) {
        int row = 0, col = 0;
        int carrierCoords[CARRIER_LENGTH * 2] = { 0 }, battleshipCoords[BATTLESHIP_LENGTH * 2] = { 0 },
                submarineCoords[SUBMARINE_LENGTH * 2] = { 0 }, cruiserCoords[CRUISER_LENGTH * 2] = { 0 }, destroyerCoords[DESTROYER_LENGTH * 2] = { 0 };
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
        if (checkPlacement(board, carrierCoords, CARRIER_LENGTH) == 0) {
            printf("That placement isn't valid! Please try again.\n");
			goto carrierPlacement;
        }
        //Carrier initialization/placement on board
        for (int i = 0; i < (CARRIER_LENGTH*2); i+=2) {
            board[carrierCoords[i]][carrierCoords[i+1]] = 'C';
        }
        printBoard(board, NUM_ROWS, NUM_COLS);

        battleshipPlacement:
        count = 0;
        printf("Please enter the cells you would like to place the battleship in:\n");
        for (int i = 0; i < (BATTLESHIP_LENGTH*2); i+=2) {
            printf("Row #%d: ", ++count);
            scanf("%d", &row);
            printf("Col #%d: ", count);
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
        if (checkPlacement(board, battleshipCoords, BATTLESHIP_LENGTH) == 0) {
            printf("That placement isn't valid! Please try again.\n");
			goto battleshipPlacement;
        }
        //Battleship initialization/placement on board
        for (int i = 0; i < (BATTLESHIP_LENGTH*2); i+=2) {
            board[battleshipCoords[i]][battleshipCoords[i + 1]] = 'B';
        }
        printBoard(board, NUM_ROWS, NUM_COLS);

        submarinePlacement:
        count = 0;
        printf("Please enter the cells you would like to place the submarine in:\n");
        for (int i = 0; i < SUBMARINE_LENGTH*2; i+=2) {
            printf("Row #%d: ", ++count);
            scanf("%d", &row);
            printf("Col #%d: ", count);
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
        if (checkPlacement(board, submarineCoords, SUBMARINE_LENGTH) == 0) {
            printf("That placement isn't valid! Please try again.\n");
			goto submarinePlacement;
        }
        //Submarine initialization/placement on board
        for (int i = 0; i < (SUBMARINE_LENGTH*2); i+=2) {
            board[submarineCoords[i]][submarineCoords[i+1]] = 'S';
        }
        printBoard(board, NUM_ROWS, NUM_COLS);

        cruiserPlacement:
        count = 0;
        printf("Please enter the cells you would like to place the cruiser in:\n");
        for (int i = 0; i < CRUISER_LENGTH*2; i+=2) {
            printf("Row #%d: ", ++count);
            scanf("%d", &row);
            printf("Col #%d: ", count);
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
        if (checkPlacement(board, cruiserCoords, CRUISER_LENGTH) == 0) {
            printf("That placement isn't valid! Please try again.\n");
			goto cruiserPlacement;
        }
        //Cruiser initialization/placement on board
        for (int i = 0; i < (CRUISER_LENGTH*2); i+=2) {
            board[cruiserCoords[i]][cruiserCoords[i+1]] = 'R';
        }
        printBoard(board, NUM_ROWS, NUM_COLS);

        destroyerPlacement:
        count = 0;
        printf("Please enter the cells you would like to place the destroyer in:\n");
        for (int i = 0; i < DESTROYER_LENGTH*2; i+=2) {
            printf("Row #%d: ", ++count);
            scanf("%d", &row);
            printf("Col #%d: ", count);
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
        if (checkPlacement(board, destroyerCoords, DESTROYER_LENGTH) == 0) {
            printf("That placement isn't valid! Please try again.\n");
			goto destroyerPlacement;
        }
        //Destroyer initialization/placement on board
        for (int i = 0; i < (DESTROYER_LENGTH*2); i+=2) {
            board[destroyerCoords[i]][destroyerCoords[i+1]] = 'D';
        }
        system("cls");
    }

    //Function checkPlacement, parameters 2D array of characters, array of integers, integer ship size.
//Iterates and sees if all row coordinates (even indices in array) are equal, OR if all column coordinates (odd indices in array) are equal.
//If so, checks if the array whose values are not all equal are sequential using bubble sort.
//Returns 1 if placement is valid, 0 if not.
    int checkPlacement(char board[][NUM_COLS], int coords[], int shipSize) {
        int rowsValid = 1, colsValid = 1, count = 0;
        int rowCheck = coords[0];
        int colCheck = coords[1];
        int rowCoords[100] = { 0 };
        int colCoords[100] = { 0 };

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
                if ((colCoords[i] > colCoords[i - 1] + 1) || board[rowCoords[i]][colCoords[i]] != '~') {
                    return 0;
                }
            }
            return 1;
        }
        else if ((!rowsValid && colsValid)) {
            //Check row values are in sequence by sorting
            bubbleSort(rowCoords, shipSize);
            for (int i = 1; i < shipSize; i++) {
                if ((rowCoords[i] > rowCoords[i - 1] + 1) || board[rowCoords[i]][colCoords[i]] != '~') {
                    return 0;
                }
            }
            return 1;
        }
        return 0;
    }

    //Function bubbleSort, sorts an array of integers in ascending order. Parameters array of integers and integer size.
//Implemented bubble sort for use in other functions.
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

    //Function isWinner, parameter 2D array of characters.
//Checks for the number of hits (asterisks) on board. If 17 (the number of hits required for a win based on ship length), returns 1 (true).
//Else, returns 0 (false).
    int isWinner(char board[][NUM_COLS]) {
        int hitCount = 0;
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (board[i][j] == '*') {
                    hitCount++;
                }
            }
        }
        if (hitCount == 17) {
            return 1;
        }
        return 0;
    }

    //Function checkShot, parameters 2D array of characters, integers xPos and yPos, character pointer.
//Checks if a shot is a hit or not based on if board at xPos, yPos is water or not.
//Returns 1 is a hit, 0 if not. Also passes value of the character hit to the indirect value of token pointer.
    int checkShot(char board[][NUM_COLS], int xPos, int yPos, char *token) {
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (i == xPos && j == yPos) {
                    if (board[i][j] != '~') {
                        if (board[i][j] != 'M' || board[i][j] != '*') {
						*token = board[i][j];
                        }
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    //Function updateBoard, parameters 2D array of characters, integers xPos and yPos, integer wannabe boolean wasHit.
//Iterates through the board and if a hit is successful, updates the board at those coordinates with an asterisk.
//If not, update the board at those coordinates with an 'M' for miss.
    void updateBoard(char board[][NUM_COLS], int xPos, int yPos, int wasHit) {
        char shipToken = '\0';
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (i == xPos && j == yPos) {
                    if (wasHit) {
                        board[i][j] = '*';
                    } else {
                        board[i][j] = 'M';
                    }
                }

            }
        }
    }

    //Function checkIfSunkShip, parameters 2D array of characters, character token.
//Checks if a ship was sunk based on the number of tokens still on the board. If there are 'none' of the given token left on the board, the ship was sunk. Returns 1.
//Else, returns 0 if there is still at least one token left on the board.
    int checkIfSunkShip(char board[][NUM_COLS], char shipToken) {
        int tokenCount = 0;
        for (int i = 0; i < NUM_ROWS; i++) {
            for (int j = 0; j < NUM_COLS; j++) {
                if (board[i][j] == shipToken) {
                    tokenCount++;
                }
            }
        }
        //Note that while the function theoretically checks if there are "no" tokens left on the board, it actually checks if there is 1 left, as this
        //function executes before the board actually updates.
        if (tokenCount == 1) {
            return 1;
        }
        return 0;
    }

    //Function outputCurrentMove, parameters file pointer outfile, integers currentPlayer, xPos, yPos, boolean-acting integers wasHit and wasSunk.
//Outputs to provided outfile moves and results of actions based on current player.
    void outputCurrentMove(FILE *outfile, int currentPlayer, int xPos, int yPos, int wasHit, int wasSunk) {
        switch (currentPlayer) {
            case 0: //Player
                if (wasHit) {
                    if (wasSunk) {
                        fprintf(outfile, "Player 1 attacked at %d, %d. It was a hit, and the enemy's ship sank!\n", xPos, yPos);
                    } else {
                        fprintf(outfile, "Player 1 attacked at %d, %d. It was a hit!\n", xPos, yPos);
                    }
                } else {
                    fprintf(outfile, "Player 1 attacked at %d, %d. It was a miss.\n", xPos, yPos);
                }
                break;
            case 1: //Computer
                if (wasHit) {
                    if (wasSunk) {
                        fprintf(outfile, "Computer attacked at %d, %d. It was a hit, and the player's ship sank!\n", xPos, yPos);
                    }
                    else {
                        fprintf(outfile, "Computer attacked at %d, %d. It was a hit!\n", xPos, yPos);
                    }
                }
                else {
                    fprintf(outfile, "Computer attacked at %d, %d. It was a miss.\n", xPos, yPos);
                }
                break;
        }
    }

    //Function outputStats, parameters file pointer outfile, Stats structs playerOne and playerTwo.
//Prints out the number of hits, misses, total number of shots, and the hit/miss ratio to outfile.
//Note that these should all be stored locally into Stats objects, then accessed with the dot operator in this function.
    void outputStats(FILE *outfile, Stats playerOne, Stats playerTwo) {
        fprintf(outfile, "Player One Stats:\n");
        fprintf(outfile, "-----------------\n");
        fprintf(outfile, "Number of Hits: %d\n", playerOne.numHits);
        fprintf(outfile, "Number of Misses: %d\n", playerOne.numMisses);
        fprintf(outfile, "Total Number of Shots: %d\n", playerOne.totalShots);
        fprintf(outfile, "Hit/Miss Ratio: %.2lf%%\n", playerOne.hitsMisses);
        fprintf(outfile, "Computer Stats:\n");
        fprintf(outfile, "-----------------\n");
        fprintf(outfile, "Number of Hits: %d\n", playerTwo.numHits);
        fprintf(outfile, "Number of Misses: %d\n", playerTwo.numMisses);
        fprintf(outfile, "Total Number of Shots: %d\n", playerTwo.totalShots);
        fprintf(outfile, "Hit/Miss Ratio: %.2lf%%\n", playerTwo.hitsMisses);
    }
}
