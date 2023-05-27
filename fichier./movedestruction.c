#include "header.h"


void displayRandomPhrase() {
    int randomIndex = rand() % 6;  // Génère un nombre aléatoire entre 0 et 5
    char* phrases[] = {
        "Nice combination!",
        "Superb shot!",
        "Impressive alignment!",
        "Beautiful game!",
        "Bravo for this combination!",
        "You are amazing!"
    };

    printf("%s\n", phrases[randomIndex]);
}


void applyGravity(int** board, int height, int length) {
    for (int i = 0; i < height; i++) {
        int emptySpaces = 0; // Compteur d'espaces vides

        // Parcours de la ligne de droite à gauche
        for (int j = length - 1; j >= 0; j--) {
            if (board[i][j] == 0) {
                emptySpaces++; // Incrémente le compteur d'espaces vides
            } else if (emptySpaces > 0) {
                // Déplacement des symboles vers la droite pour remplir les espaces vides
                board[i][j + emptySpaces] = board[i][j];
                board[i][j] = 0;
            }
        }
    }
}

void fillEmptySpaces(int** board, int height, int length, int symbols) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            if (board[i][j] == 0) {
                board[i][j] = rand() % symbols + 1; // Remplit les espaces vides avec de nouvelles valeurs aléatoires
            }
        }
    }
}

int canMakeAlignment(int** board, int height, int length) {
    int alignmentCount = 0; // Compteur d'alignements identiques

    // Recherche d'un alignement horizontal
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length - 2; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                // Recherche d'un symbole identique ailleurs dans la grille
                alignmentCount = 0;
                for (int x = 0; x < height; x++) {
                    for (int y = 0; y < length; y++) {
                        if ((x != i || y != j) && (board[x][y] != 0) && (board[x][y] == board[i][j])) {
                            alignmentCount++;
                        }
                    }
                }
            }
        }
    }

    // Recherche d'un alignement vertical
    for (int j = 0; j < length; j++) {
        for (int i = 0; i < height - 2; i++) {
            if (board[i][j] != 0 && board[i][j] == board[i + 1][j]) {
                // Recherche d'un symbole identique ailleurs dans la grille
                alignmentCount = 0;
                for (int x = 0; x < height; x++) {
                    for (int y = 0; y < length; y++) {
                        if ((x != i || y != j) && (board[x][y] != 0) && (board[x][y] == board[i][j])) {
                            alignmentCount++;
                        }
                    }
                }
            }
        }
    }

    if (alignmentCount >= 2) {
        return 1; // Au moins trois symboles identiques ont été trouvés
    } else {
        return 0; // Moins de trois symboles identiques trouvés
    }
}




void checkSymbolsAdjacent(int** board, int height, int length, int numSymbols) {
    int symbolsRemoved = 0;
    int symbolsAdjacent = 1;

    while (symbolsAdjacent) {
        symbolsAdjacent = 0;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                int symbol = board[i][j];

                // Vérification des symboles adjacents horizontaux
                if (symbol != 0 && j < length - 2 && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                    board[i][j] = 0;
                    board[i][j + 1] = 0;
                    board[i][j + 2] = 0;
                    symbolsRemoved += 3;
                    symbolsAdjacent = 1;
                } else if (symbol != 0 && j == length - 2 && board[i][j + 1] == symbol && board[i][0] == symbol) {
                    board[i][j] = 0;
                    board[i][j + 1] = 0;
                    board[i][0] = 0;
                    symbolsRemoved += 3;
                    symbolsAdjacent = 1;
                } else if (symbol != 0 && j == length - 1 && board[i][0] == symbol && board[i][1] == symbol) {
                    board[i][j] = 0;
                    board[i][0] = 0;
                    board[i][1] = 0;
                    symbolsRemoved += 3;
                    symbolsAdjacent = 1;
                }

                // Vérification des symboles adjacents verticaux
                if (symbol != 0 && i < height - 2 && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                    board[i][j] = 0;
                    board[i + 1][j] = 0;
                    board[i + 2][j] = 0;
                    symbolsRemoved += 3;
                    symbolsAdjacent = 1;
                } else if (symbol != 0 && i == height - 2 && board[i + 1][j] == symbol && board[0][j] == symbol) {
                    board[i][j] = 0;
                    board[i + 1][j] = 0;
                    board[0][j] = 0;
                    symbolsRemoved += 3;
                    symbolsAdjacent = 1;
                } else if (symbol != 0 && i == height - 1 && board[0][j] == symbol && board[1][j] == symbol) {
                    board[i][j] = 0;
                    board[0][j] = 0;
                    board[1][j] = 0;
                    symbolsRemoved += 3;
                    symbolsAdjacent = 1;
                }
            }
        }

        if (symbolsRemoved) {
            applyGravity(board, height, length);
            fillEmptySpaces(board, height, length, numSymbols); // Remplir les espaces vides avec de nouveaux symboles
            symbolsRemoved = 0;
        }
    }
}

void checkAndCollapse(int** board, int height, int length, int* score, int numSymbols) {
    int collapse = 0;
    int symbolsDestroyed = 0;
// Vérification des combinaisons horizontales
    for (int i = 0; i < height; i++) {
        int count = 1; // Variable pour compter le nombre de symboles alignés
        for (int j = 0; j < length - 1; j++) {
            int symbol = board[i][j];
            if (symbol != 0 && board[i][j + 1] == symbol) {
                count++;
            } else {
                if (count >= 3) {
                    for (int k = 0; k < count; k++) {
                        board[i][j - k] = 0;
                    }
                    collapse = 1;
                    symbolsDestroyed += count;
                }
                count = 1;
            }
        }
        // Vérifier une dernière fois après la boucle pour le dernier groupe de symboles alignés
        if (count >= 3) {
            for (int k = 0; k < count; k++) {
                board[i][length - 1 - k] = 0;
            }
            collapse = 1;
            symbolsDestroyed += count;
        }
    }

    // Vérification des combinaisons verticales
    for (int j = 0; j < length; j++) {
        int count = 1; // Variable pour compter le nombre de symboles alignés
        for (int i = 0; i < height - 1; i++) {
            int symbol = board[i][j];
            if (symbol != 0 && board[i + 1][j] == symbol) {
                count++;
            } else {
                if (count >= 3) {
                    for (int k = 0; k < count; k++) {
                        board[i - k][j] = 0;
                    }
                    collapse = 1;
                    symbolsDestroyed += count;
                }
                count = 1;
            }
        }
        // Vérifier une dernière fois après la boucle pour le dernier groupe de symboles alignés
        if (count >= 3) {
            for (int k = 0; k < count; k++) {
                board[height - 1 - k][j] = 0;
            }
            collapse = 1;
            symbolsDestroyed += count;
        }
    }

    // Vérification des combinaisons sur les bords verticaux
    for (int j = 0; j < length; j++) {
        int symbol = board[height - 2][j];
        if (symbol != 0 && board[height - 1][j] == symbol && board[0][j] == symbol) {
            board[height - 2][j] = 0;
            board[height - 1][j] = 0;
            board[0][j] = 0;
            collapse = 1;
        }

        symbol = board[height - 1][j];
        if (symbol != 0 && board[0][j] == symbol && board[1][j] == symbol) {
            board[height - 1][j] = 0;
            board[0][j] = 0;
            board[1][j] = 0;
            collapse = 1;
        }
    }

    // Vérification des combinaisons sur les bords horizontaux
    for (int i = 0; i < height; i++) {
        int symbol = board[i][length - 2];
        if (symbol != 0 && board[i][length - 1] == symbol && board[i][0] == symbol) {
            board[i][length - 2] = 0;
            board[i][length - 1] = 0;
            board[i][0] = 0;            
            collapse = 1;
        }

        symbol = board[i][length - 1];
        if (symbol != 0 && board[i][0] == symbol && board[i][1] == symbol) {
            board[i][length - 1] = 0;
            board[i][0] = 0;
            board[i][1] = 0;
            collapse = 1;
        }
    }

    if (collapse) {
        symbolsDestroyed += 3;
        applyGravity(board, height, length);
        fillEmptySpaces(board, height, length, numSymbols); // 6 est le nombre de symboles possibles
        checkAndCollapse( board, height, length, score, numSymbols);
    }
    *score += symbolsDestroyed; // Ajouter le nombre de symboles détruits au score
}


int hasMatch(int** board, int height, int length, int row, int col) {
    int symbol = board[row][col];

    // Vérification des lignes horizontales
    if (col >= 2 && board[row][col - 1] == symbol && board[row][col - 2] == symbol) {
        return 1;
    }
    if (col <= length - 3 && board[row][col + 1] == symbol && board[row][col + 2] == symbol) {
        return 1;
    }
    if (col == 0 && board[row][length - 1] == symbol && board[row][length - 2] == symbol) {
        return 1;
    }
    if (col == length - 1 && board[row][0] == symbol && board[row][1] == symbol) {
        return 1;
    }

    // Vérification des colonnes verticales
    if (row >= 2 && board[row - 1][col] == symbol && board[row - 2][col] == symbol) {
        return 1;
    }
    if (row <= height - 3 && board[row + 1][col] == symbol && board[row + 2][col] == symbol) {
        return 1;
    }
    if (row == 0 && board[height - 1][col] == symbol && board[height - 2][col] == symbol) {
        return 1;
    }
    if (row == height - 1 && board[0][col] == symbol && board[1][col] == symbol) {
        return 1;
    }

   if (row == 0 && board[height - 1][col] == symbol && board[height - 2][col] == symbol) {
        return 1;
    }
    if (row == height - 1 && board[0][col] == symbol && board[1][col] == symbol) {
        return 1;
    }

    // Bord de gauche et de droite
    if (col == 0 && board[row][length - 1] == symbol && board[row][length - 2] == symbol) {
        return 1;
    }
    if (col == length - 1 && board[row][0] == symbol && board[row][1] == symbol) {
        return 1;
    }

    // Vérification des correspondances spécifiques aux bords connectés
    // Bord de gauche et extrémité droite
    if (col == 0 && board[row][length - 1] == symbol && board[row][length - 2] == symbol && board[row][1] == symbol) {
        return 1;
    }
    // Extrémité droite et bord de gauche
    if (col == length - 1 && board[row][0] == symbol && board[row][1] == symbol && board[row][length - 2] == symbol) {
        return 1;
    }

    return 0; // Aucun match trouvé
}


void swapSymbols(int** board, int height, int length, int score, int row1, int col1, int row2, int col2, int numSymbols) {
    int temp = board[row1][col1];
    board[row1][col1] = board[row2][col2];
    board[row2][col2] = temp;
   int match1 = hasMatch(board, height, length, row1, col1);
    int match2 = hasMatch(board, height, length, row2, col2);

    if (!match1 && !match2) {
        // Aucun match n'a été créé, annule le mouvement
        temp = board[row1][col1];
        board[row1][col1] = board[row2][col2];
        board[row2][col2] = temp;
        printf("No match found. Try again.\n");
        return;
    }
}
