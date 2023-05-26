#include "header.h"

void applyGravity(int** board, int height, int length) {
    for (int i = 0; i < height; i++) {
        for (int j = length - 1; j >= 0; j--) {
            if (board[i][j] == 0) {
                for (int k = j; k > 0; k--) {
                    board[i][k] = board[i][k - 1];
                }
                board[i][0] = 0;
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
    // Recherche d'un alignement horizontal
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length - 2; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                // Recherche d'un symbole identique ailleurs dans la grille
                for (int x = 0; x < height; x++) {
                    for (int y = 0; y < length; y++) {
                        if ((x != i || y != j) && (board[x][y] != 0) && (board[x][y] == board[i][j])) {
                            return 1; // Alignement possible trouvé
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
                for (int x = 0; x < height; x++) {
                    for (int y = 0; y < length; y++) {
                        if ((x != i || y != j) && (board[x][y] != 0) && (board[x][y] == board[i][j])) {
                            return 1; // Alignement possible trouvé
                        }
                    }
                }
            }
        }
    }

    return 0; // Aucun alignement possible trouvé
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

    if (collapse) {
        *score += symbolsDestroyed; // Ajouter le nombre de symboles détruits au score
        applyGravity(board, height, length);
        fillEmptySpaces(board, height, length, numSymbols); // 6 est le nombre de symboles possibles
        checkAndCollapse(board, height, length, score, numSymbols);
    }
}

int hasMatch(int** board, int height, int length, int row, int col) {
    int symbol = board[row][col];
    int matchFound = 0;

    // Phrases "Belle combinaison" possibles
    const char* phrases[] = {
        "Belle combinaison !",
        "Superbe alignement !",
        "Impressionnant ! Une combinaison !",
        "Magnifique ! C'est un match !",
        "Wow ! Regardez cette combinaison !",
        "Incroyable ! Vous avez trouvé un alignement !",
        "Bravo ! C'est un superbe alignement !",
        "Fantastique ! Une combinaison parfaite !",
        "Extraordinaire ! Un alignement incroyable !",
        "Exceptionnel ! C'est une combinaison géniale !"
    };

    int numPhrases = sizeof(phrases) / sizeof(phrases[0]);

    // Tableau pour suivre les phrases déjà utilisées
    static int usedPhrases[10] = { 0 };

    // Vérifier combien de phrases ont été utilisées
    int phrasesUsed = 0;
    for (int i = 0; i < numPhrases; i++) {
        if (usedPhrases[i] == 1) {
            phrasesUsed++;
        }
    }

    // Si toutes les phrases ont été utilisées, réinitialiser le tableau usedPhrases
    if (phrasesUsed == numPhrases) {
        for (int i = 0; i < numPhrases; i++) {
            usedPhrases[i] = 0;
        }
        phrasesUsed = 0;
    }

    // Sélection aléatoire d'une phrase non utilisée
    srand(time(NULL));
    int randomIndex = rand() % numPhrases;
    while (usedPhrases[randomIndex] == 1) {
        randomIndex = rand() % numPhrases;
    }
    usedPhrases[randomIndex] = 1;

    const char* phrase = phrases[randomIndex];

    // Vérification des combinaisons horizontales
    if (col >= 2 && board[row][col - 1] == symbol && board[row][col - 2] == symbol) {
        matchFound = 1;
    }
    else if (col <= length - 3 && board[row][col + 1] == symbol && board[row][col + 2] == symbol) {
        matchFound = 1;
    }
    else if (col == 0 && board[row][length - 1] == symbol && board[row][length - 2] == symbol) {
        matchFound = 1;
    }
    else if (col == length - 1 && board[row][0] == symbol && board[row][1] == symbol) {
        matchFound = 1;
    }

    // Vérification des combinaisons verticales
    else if (row >= 2 && board[row - 1][col] == symbol && board[row - 2][col] == symbol) {
        matchFound = 1;
    }
    else if (row <= height - 3 && board[row + 1][col] == symbol && board[row + 2][col] == symbol) {
        matchFound = 1;
    }
    else if (row == 0 && board[height - 1][col] == symbol && board[height - 2][col] == symbol) {
        matchFound = 1;
    }
    else if (row == height - 1 && board[0][col] == symbol && board[1][col] == symbol) {
        matchFound = 1;
    }

    // Affichage de la phrase uniquement lorsque matchFound est vrai
    if (matchFound) {
        printf("%s\n", phrase);
    }

    return matchFound;
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
        printf("Aucun match trouvé. Réessayez.\n");
        return;
    }
}
