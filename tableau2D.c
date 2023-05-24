#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void displayBoard(int** board, int height, int length, int *score) {
         printf("\033[H\033[J");
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
                    if (board[i][0] != board[i][length - 1]) {
                        symbol = rand() % symbols + 1;
                    }
                } else if (j == 0 && board[i][length - 1] == symbol && board[i][length - 2] == symbol) {
                    count++;
                    if (board[i][length - 1] != board[i][0]) {
                        symbol = rand() % symbols + 1;
                    }
                }

                // Vérifie la connexion des bords opposés verticalement
                if (i == height - 1 && board[0][j] == symbol && board[1][j] == symbol) {
                    count++;
                    if (board[0][j] != board[height - 1][j]) {
                        symbol = rand() % symbols + 1;
                    }
                } else if (i == 0 && board[height - 1][j] == symbol && board[height - 2][j] == symbol) {
                    count++;
                    if (board[height - 1][j] != board[0][j]) {
                        symbol = rand() % symbols + 1;
                    }
                }

            } while (count >= 1);

            board[i][j] = symbol;
        }
    }
}

int canMakeAlignment(int** board, int height, int length, int score) {
    int canAlign = 0;
    int continueGame = 1;

    // Recherche d'un alignement horizontal
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length - 2; j++) {
            if (board[i][j] != 0 && board[i][j] == board[i][j + 1]) {
                // Recherche d'un symbole identique ailleurs dans la grille
                for (int x = 0; x < height; x++) {
                    for (int y = 0; y < length; y++) {
                        if ((x != i || y != j) && (board[x][y] != 0) && (board[x][y] == board[i][j])) {
                            canAlign = 1;
                            return canAlign; // Alignement possible trouvé
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
                            canAlign = 1;
                            return canAlign; // Alignement possible trouvé
                        }
                    }
                }
            }
        }
    }

    if (canAlign == 0) {
        printf("Partie terminée ! Score final : %d\n", score);
        continueGame = 0;
    }

    return continueGame; // 0 si la partie doit s'arrêter, 1 si la partie doit continuer
}



void checkAndCollapse(int** board, int height, int length, int* score, int numSymbols) {
    int collapse = 0;
    int symbolsDestroyed = 0;
    // Vérification des combinaisons horizontales
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length - 2; j++) {
            int symbol = board[i][j];
            if (symbol != 0 && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                board[i][j] = 0;
                board[i][j + 1] = 0;
                board[i][j + 2] = 0;
                collapse = 1;
            }
        }
    }

    // Vérification des combinaisons verticales
    for (int i = 0; i < height - 2; i++) {
        for (int j = 0; j < length; j++) {
            int symbol = board[i][j];
            if (symbol != 0 && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                board[i][j] = 0;
                board[i + 1][j] = 0;
                board[i + 2][j] = 0;
                collapse = 1;
            }
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
        symbolsDestroyed += 3; // Chaque effondrement détruit 3 symboles
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

    // Vérification des correspondances avec les bords
    // Bord du haut et du bas
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
        printf("Aucun match trouvé. Réessayez.\n");
        return;
    }
}




void sauvegarderPartie(const char* nomFichier, int hauteur, int longueur, int symboles, int score) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        if (fprintf(fichier, "%d\n%d\n%d\n%d", hauteur, longueur, symboles, score) < 0) {
            printf("Erreur lors de l'écriture dans le fichier de sauvegarde.\n");
        } else {
            fclose(fichier);
            printf("Partie sauvegardée avec succès.\n");
        }
    } else {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    }
}

void chargerPartie(const char* nomFichier, int* hauteur, int* longueur, int* symboles, int* score) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        if (fscanf(fichier, "%d\n%d\n%d\n%d", hauteur, longueur, symboles, score) < 4) {
            printf("Erreur lors de la lecture du fichier de sauvegarde.\n");
        } else {
            fclose(fichier);
            printf("Partie chargée avec succès.\n");
        }
    } else {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    }
}


int main() {

    int choix;

    printf("\033[1;34m╔════════════════════════════════════╗\n");
    printf("║\033[1;36m      Bienvenue dans CY Crush       \033[1;34m║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║              Menu:                 ║\n");
    printf("║                                    ║\n");
    printf("║\033[1;33m          1) Jouer                  \033[1;34m║\n");
    printf("║\033[1;33m          2) Charger une partie     \033[1;34m║\n");
    printf("║\033[1;33m          3) Quitter                \033[1;34m║\n");
    printf("║                                    ║\n");
    printf("╠════════════════════════════════════╣\n");
    printf("║    ");
    printf("\033[1;31m  Choisissez une option         \033[1;34m");
    printf("║\n");
    printf("╚════════════════════════════════════╝\n");
    scanf("%d", &choix);

    switch (choix) {
    case 1:
        printf("\033[1;34m\n\n");
        printf("╔════════════════════════════════════╗\n");
        printf("║\033[1;36m      Lancement du jeu...           \033[1;34m║\n");
        printf("║                                    ║\n");
        printf("║\033[1;35m      Instructions du jeu :        \033[1;34m║\n");
        printf("║                                    ║\n");
        printf("║      - Détruisez le plus de        ║\n");
        printf("║        symboles possible.          ║\n");
        printf("║      - Vous pouvez interchanger    ║\n");
        printf("║        n'importe quel symbole de   ║\n");
        printf("║        la grille.                  ║\n");
        printf("║      - Les bords sont connectés.   ║\n");
        printf("║      - Faites des combinaisons de  ║\n");
        printf("║        3 symboles identiques ou    ║\n");
        printf("║        plus pour augmenter         ║\n");
        printf("║        votre score.                ║\n");
        printf("║      - Sauvegardez votre partie et ║\n");
        printf("║        consultez votre score dans  ║\n");
        printf("║        les meilleurs scores.       ║\n");
        printf("║                                    ║\n");
        printf("╚════════════════════════════════════╝\n");
        break;
    case 2:
    printf("\033[1;34mChargement de la partie...\n");
    {
        int hauteur, longueur, symboles, score;
        const char* nomFichier = "nom_de_votre_fichier.txt";  // Remplacez "nom_de_votre_fichier.txt" par le nom réel de votre fichier de sauvegarde

        chargerPartie(nomFichier, &hauteur, &longueur, &symboles, &score);

        // Ajoutez ici le code pour continuer le jeu à partir du point de chargement
        printf("Partie chargée avec succès.\n");
        printf("Hauteur : %d\n", hauteur);
        printf("Longueur : %d\n", longueur);
        printf("Symboles : %d\n", symboles);
        printf("Score : %d\n", score);

        // Poursuivre le jeu avec les données chargées
        // ...

        printf("Le jeu a été repris à partir de la sauvegarde.\n");
    }
    break;
    case 3:
        printf("Au revoir !\n");
        return 0;
    default:
        printf("Option invalide. Veuillez choisir une option valide.\n");
        return 0;
}
    // Si l'option choisie n'est pas "Quitter", vous pouvez ajouter ici le reste du code du jeu



    int height, length, symbols;
    int score = 0;

    while (1) {
        printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
        printf("Entrez la hauteur de la grille : ");
        printf("\033[0m"); // Réinitialisation des couleurs

        if (scanf("%d", &height) != 1 || height <= 0) {
            printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
            printf("La hauteur de la grille doit être un nombre entier positif. Réessayez.\n");
            printf("\033[0m"); // Réinitialisation des couleurs
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    while (1) {
        printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
        printf("Entrez la longueur de la grille : ");
        printf("\033[0m"); // Réinitialisation des couleurs

        if (scanf("%d", &length) != 1 || length <= 0) {
            printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
            printf("La longueur de la grille doit être un entier positif. Réessayez.\n");
            printf("\033[0m"); // Réinitialisation des couleurs
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    while (1) {
        printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
        printf("Entrez le nombre de symboles (entre 4 et 6) : ");
        printf("\033[0m"); // Réinitialisation des couleurs

        if (scanf("%d", &symbols) != 1 || symbols < 4 || symbols > 6) {
            printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
            printf("Le nombre de symboles doit être un nombre entier entre 4 et 6. Réessayez.\n");
            printf("\033[0m"); // Réinitialisation des couleurs
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    printf("\n\n"); // Ligne vide pour l'aération
    printf("\033[1;33m"); // Couleur jaune vif pour le texte de confirmation
    printf("Grille créée : hauteur = %d, longueur = %d, symboles = %d\n", height, length, symbols);
    printf("\033[0m"); // Réinitialisation des couleurs




    int** board = malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        board[i] = calloc(length, sizeof(int));
    }

    boardInitializer(board, height, length, symbols);
    displayBoard(board, height, length,&score);
    

    while (1) {
        int row1, col1, row2, col2;

        printf("Choisissez les coordonnées du premier symbole à interchanger (lettre chiffre) : ");
        char column1;
        if (scanf(" %c%d", &column1, &row1) != 2 || row1 < 1 || row1 > height || column1 < 'A' || column1 > 'A' + length) {
            printf("Coordonnées invalides. Réessayez.\n");
            continue;
        }
        col1 = column1 - 'A';

        printf("Choisissez les coordonnées du deuxième symbole à interchanger (lettre chiffre) : ");
        char column2;
        if (scanf(" %c%d", &column2, &row2) != 2 || row2 < 1 || row2 > height || column2 < 'A' || column2 > 'A' + length) {
            printf("Coordonnées invalides. Réessayez.\n");
            continue;
        }
        col2 = column2 - 'A';

        // Interchange les symboles sélectionnés
        swapSymbols(board, height, length,score, row1 - 1, col1, row2 - 1, col2, symbols);
        // Vérifie si l'interchange a créé au moins trois symboles identiques
        int** copy = board_copy(board, height, length);
        if (verifyInitialization(copy, height, length)) {
            canMakeAlignment(board, height, length, score);
            checkAndCollapse( board, height, length,&score, symbols);
            applyGravity(board, height, length);
            fillEmptySpaces(board, height, length, symbols);
            displayBoard(board, height, length,&score);
        } else {
            printf("L'interchange ne crée pas au moins trois symboles identiques. Réessayez.\n");
        }

        for (int i = 0; i < height; i++) {
            free(copy[i]);
        }
        free(copy);
    }
    for (int i = 0; i < height; i++) {
        free(board[i]);
    }
    free(board);
    
return 0;
}
