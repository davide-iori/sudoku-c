#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define MAT_SIDE 9
#define SUBMAT_SIDE 3


/* draws a side*side sudoku board using the specified chatacters for the horizontal and vertical lines (e.g. '+' for vertical and '-' for horizontal) */
void drawBoard(int numbers[][MAT_SIDE]);
void displayMenu();
void startGame(char startingString[], int mat[][MAT_SIDE], char outGameStr[]);
int isResolved(int mat[][MAT_SIDE]);
void setNonCanonicalMode();

#endif