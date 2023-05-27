#include "header.h"

void displayBoard(int** board, int height, int length, int *score) {
        printf("Score: %d\n", *score);
    // Affichage de l'en-tête des colonnes
    printf("  ");
    for (int j = 0; j < length; j++) {
        printf("%c ", 'A' + j);
    }
    printf("\n");
;
    for (int i = 0; i < height; i++) {
        // Affichage du numéro de la ligne
        printf("%d ", i + 1);

        for (int j = 0; j < length; j++) {
            switch (board[i][j]) {
                case 1:
                    printf("\033[1;31m♥\033[0m "); // cœur rouge
                    break;
                case 2:
                    printf("\033[1;37m♡\033[0m "); // cœur blanc
                    break;
                case 3:
                    printf("\033[1;32m♦\033[0m "); // carreau vert
                    break;
                case 4:
                    printf("\033[1;33m♢\033[0m "); // carreau jaune
                    break;
                case 5:
                    printf("\033[1;34m♣\033[0m "); // trèfle bleu
                    break;
                case 6:
                    printf("\033[1;35m♠\033[0m "); // pique rose
                    break;
                default:
                    printf("  "); // Espace par défaut
                    break;
            }
        }
        printf("\n");
    }
    sleep(1);
}


int verifyInitialization(int** board, int height, int length) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            if (board[i][j] == 0) {
                return 0; // Le tableau n'est pas correctement initialisé
            }
        }
    }
    return 1; // Le tableau est correctement initialisé
}


int** board_copy(int** board, int height, int length) {
    int** copy = malloc(height * sizeof(int*));

    for (int i = 0; i < height; i++) {
        copy[i] = malloc(length * sizeof(int));
        for (int j = 0; j < length; j++) {
            copy[i][j] = board[i][j];
        }
    }

    return copy;
}

void boardInitializer(int** board, int height, int length, int symbols) {
    srand(time(NULL));

    // Initialisation de la grille avec des symboles aléatoires
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            int symbol;
            int count = 0;

            do {
                symbol = rand() % symbols + 1; // Génère un nombre aléatoire entre 1 et le nombre de symboles inclus
                count = 0;

                // Vérifie les symboles adjacents horizontalement
                if (j >= 2 && board[i][j - 1] == symbol && board[i][j - 2] == symbol) {
                    count++;
                } else if (j == 1 && board[i][0] == symbol && board[i][length - 1] == symbol) {
                    count++;
                } else if (j == 0 && board[i][length - 1] == symbol && board[i][length - 2] == symbol) {
                    count++;
                }

                // Vérifie les symboles adjacents verticalement
                if (i >= 2 && board[i - 1][j] == symbol && board[i - 2][j] == symbol) {
                    count++;
                } else if (i == 1 && board[0][j] == symbol && board[height - 1][j] == symbol) {
                    count++;
                } else if (i == 0 && board[height - 1][j] == symbol && board[height - 2][j] == symbol) {
                    count++;
                }

                // Vérifie la connexion des bords opposés horizontalement
                if (j == length - 1 && board[i][0] == symbol && board[i][1] == symbol) {
                    count++;
                    if (board[i][0] != board[i][j]) {
                        symbol = rand() % symbols + 1;
                        count = 0; // Réinitialise le compteur pour réévaluer la nouvelle valeur de symbol
                    }
                } else if (j == 0 && board[i][length - 1] == symbol && board[i][length - 2] == symbol) {
                    count++;
                    if (board[i][length - 1] != board[i][j]) {
                        symbol = rand() % symbols + 1;
                        count = 0; // Réinitialise le compteur pour réévaluer la nouvelle valeur de symbol
                    }
                }

                // Vérifie la connexion des bords opposés verticalement
                if (i == height - 1 && board[0][j] == symbol && board[1][j] == symbol) {
                    count++;
                    if (board[0][j] != board[i][j]) {
                        symbol = rand() % symbols + 1;
                        count = 0; // Réinitialise le compteur pour réévaluer la nouvelle valeur de symbol
                    }
                } else if (i == 0 && board[height - 1][j] == symbol && board[height - 2][j] == symbol) {
                    count++;
                    if (board[height - 1][j] != board[i][j]) {
                        symbol = rand() % symbols + 1;
                        count = 0; // Réinitialise le compteur pour réévaluer la nouvelle valeur de symbol
                    }
                }

            } while (count >= 1);

            board[i][j] = symbol;
        }
    }
}


