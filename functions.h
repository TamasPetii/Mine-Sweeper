#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void options(int*);
void newGame(int, char**);
void loadGame();
int NumofMines(int, char**);
void InsertMines(char**, int);
void PrintField(char**);
void FillField(char**);
void Game(char**, char**, int*);
void loading(char**, char**, int*);
void saving(char**, char**, int);
int check(char**, char*);
void rev(char**, char**, int, int, int*);
void freeMemory(char**, char**);
#endif