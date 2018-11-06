/*Header here*/
//Functions generateDirection, generateStartingPoint, and placeShip adapted from Andrew O'Fallon.
#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define HORIZONTAL 0
#define VERTICAL 1
#define NUM_ROWS 10
#define NUM_COLS 10
#define CARRIER_LENGTH 5
#define BATTLESHIP_LENGTH 4
#define SUBMARINE_LENGTH 3
#define CRUISER_LENGTH 3
#define DESTROYER_LENGTH 2

//Datatype initialization
typedef struct {
	int numHits, numMisses, totalShots;
	double hitsMisses;
} Stats;

//Function prototypes
void initializeBoard(char board[10][10], int numRows, int numColumns);

void printBoard(char board[10][10], int numRows, int numColumns);

int generateDirection(void);

void generateStartingPoint(int direction, int shipLength, int *row, int *column);

void placeShip(char board[][NUM_COLS], int numRows, int numCols, int shipLength, char shipSymbol, int direction, int rowStart, int colStart);

int detectCollision(char board[][NUM_COLS], int direction, int shipLength, int row, int col);

int selectWhoStartsFirst(void);

void manuallyPlaceShips(char board[][NUM_COLS]);

int checkPlacement(char board[][NUM_COLS], int coords[], int shipSize);

void bubbleSort(int arr[], int size);

int isWinner(char board[][NUM_COLS]);

void updateBoard(char board[][NUM_COLS], int xPos, int yPos, int wasHit);

int checkShot(char board[][NUM_COLS], int xPos, int yPos, char *token);

int checkIfSunkShip(char board[][NUM_COLS], char shipToken);

void outputCurrentMove(FILE *outfile, int currentPlayer, int xPos, int yPos, int wasHit, int wasSunk);

void outputStats(FILE *outfile, Stats playerOne, Stats playerTwo);

#endif