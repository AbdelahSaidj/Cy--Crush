#ifndef HEADER_H
#define HEADER_H
#include "header.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <termios.h>

void displayBoard(int** board, int height, int length, int *score);
int verifyInitialization(int** board, int height, int length);
int** board_copy(int** board, int height, int length);
void applyGravity(int** board, int height, int length);
void fillEmptySpaces(int** board, int height, int length, int symbols);
void boardInitializer(int** board, int height, int length, int symbols);
int canMakeAlignment(int** board, int height, int length);
void checkAndCollapse(int** board, int height, int length, int* score, int numSymbols);
int hasMatch(int** board, int height, int length, int row, int col);
void swapSymbols(int** board, int height, int length, int score, int row1, int col1, int row2, int col2, int numSymbols);
void sauvegarderPartie(const char* nomFichier, int hauteur, int longueur, int symboles, int score, int** plateau);
void chargerPartie(const char* nomFichier, int* hauteur, int* longueur, int* symboles, int* score, int*** plateau);
void obtenirCheminSauvegarde(char* chemin);
void afficherSauvegardes();

#endif
