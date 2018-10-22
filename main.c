#include "game.h"

int main(void) {
	char playerOneBoard[10][10] = { {'\0'} };
	initializeBoard(playerOneBoard, 10, 10);
	printBoard(playerOneBoard, 10, 10);
	return 0; //End of main function
}