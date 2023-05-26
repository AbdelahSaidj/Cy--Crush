#include "header.h"

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
            printf("║\033[1;35m      Instructions du jeu :         \033[1;34m║\n");
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
            printf("║      - Appuyez sur E puis entrer à ║\n");
            printf("║        tout moment pour quitter    ║\n");
            printf("║        votre partie.               ║\n");
            printf("╚════════════════════════════════════╝\n");
            break;
       case 2:
    {
        int hauteur, longueur, symboles, score;
        int** plateau = NULL;

        // Afficher les sauvegardes disponibles
        printf("Liste des sauvegardes :\n");
        afficherSauvegardes();

        // Demander à l'utilisateur de sélectionner une sauvegarde
        int selection;
        printf("Veuillez entrer le numéro de la sauvegarde que vous souhaitez charger : ");
        scanf("%d", &selection);

        // Construire le nom de fichier correspondant à la sauvegarde sélectionnée
        char nomSauvegarde[100];
        snprintf(nomSauvegarde, sizeof(nomSauvegarde), "sauvegarde%d.txt", selection);

        chargerPartie(nomSauvegarde, &hauteur, &longueur, &symboles, &score, &plateau);

        if (plateau != NULL) {
            // Ajoutez ici le code pour continuer le jeu à partir du point de chargement
            printf("\033[1;34mChargement de la partie...\n");
            printf("Partie chargée avec succès.\n");
            printf("Hauteur : %d\n", hauteur);
            printf("Longueur : %d\n", longueur);
            printf("Symboles : %d\n", symboles);
            printf("Score : %d\n", score);

            // Poursuivre le jeu avec les données chargées
            // ...

            // Libérer la mémoire allouée pour le plateau de jeu
            for (int i = 0; i < hauteur; i++) {
                free(plateau[i]);
            }
            free(plateau);

            printf("Le jeu a été repris à partir de la sauvegarde.\n");
        } else {
            printf("Erreur lors du chargement de la partie. Veuillez vérifier le fichier de sauvegarde.\n");
        }
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

        char* input = malloc(sizeof(char) * 100); // Allocation dynamique de mémoire pour l'entrée
        scanf("%s", input);

        if (strcmp(input, "E") == 0 || strcmp(input, "e") == 0) {
            printf("Au revoir !\n");
            free(input); // Libération de la mémoire allouée dynamiquement
            return 0;
        }
      
        if (sscanf(input, "%d", &height) != 1 || height < 3 || height > 25) {
            printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
            printf("La hauteur de la grille doit être un nombre entier entre 3 et 25 inclus. Réessayez.\n");
            printf("\033[0m"); // Réinitialisation des couleurs
        } else {
            free(input); // Libération de la mémoire allouée dynamiquement
            break;
        }
    }

    while (1) {
        printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
        printf("Entrez la longueur de la grille : ");
        printf("\033[0m"); // Réinitialisation des couleurs

        char* input = malloc(sizeof(char) * 100); // Allocation dynamique de mémoire pour l'entrée
        scanf("%s", input);

        if (strcmp(input, "E") == 0 || strcmp(input, "e") == 0) {
            printf("Au revoir !\n");
            free(input); // Libération de la mémoire allouée dynamiquement
            return 0;
        }

        if (sscanf(input, "%d", &length) != 1 || length < 3 || length > 25) {
            printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
            printf("La longueur de la grille doit être un nombre entier entre 3 et 25 inclus. Réessayez.\n");
            printf("\033[0m"); // Réinitialisation des couleurs
        } else {
            free(input); // Libération de la mémoire allouée dynamiquement
            break;
        }
    }

    while (1) {
        printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
        printf("Entrez le nombre de symboles (entre 4 et 6) : ");
        printf("\033[0m"); // Réinitialisation des couleurs

        char* input = malloc(sizeof(char) * 100); // Allocation dynamique de mémoire pour l'entrée
        scanf("%s", input);

        if (strcmp(input, "E") == 0 || strcmp(input, "e") == 0) {
            printf("Au revoir !\n");
            free(input); // Libération de la mémoire allouée dynamiquement
            return 0;
        }

        if (sscanf(input, "%d", &symbols) != 1 || symbols < 4 || symbols > 6) {
            printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
            printf("Le nombre de symboles doit être un nombre entier entre 4 et 6. Réessayez.\n");
            printf("\033[0m"); // Réinitialisation des couleurs
        } else {
            free(input); // Libération de la mémoire allouée dynamiquement
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
displayBoard(board, height, length, &score);

while (1) {
    int row1, col1, row2, col2;

    printf("Choisissez les coordonnées du premier symbole à interchanger (lettre chiffre) : ");
    char column1;
    char input1[100];
    scanf("%s", input1);

    if (strcmp(input1, "E") == 0 || strcmp(input1, "e") == 0) {
        printf("Au revoir !\n");
        break;
    }

    if (sscanf(input1, " %c%d", &column1, &row1) != 2 || row1 < 1 || row1 > height || column1 < 'A' || column1 > 'A' + length) {
        printf("Coordonnées invalides. Réessayez.\n");
        continue;
    }
    col1 = column1 - 'A';

    printf("Choisissez les coordonnées du deuxième symbole à interchanger (lettre chiffre) : ");
    char column2;
    char input2[100];
    scanf("%s", input2);

    if (strcmp(input2, "E") == 0 || strcmp(input2, "e") == 0) {
        printf("Au revoir !\n");
        break;
    }

    if (sscanf(input2, " %c%d", &column2, &row2) != 2 || row2 < 1 || row2 > height || column2 < 'A' || column2 > 'A' + length) {
        printf("Coordonnées invalides. Réessayez.\n");
        continue;
    }
    col2 = column2 - 'A';


    // Interchange les symboles sélectionnés
    swapSymbols(board, height, length, score, row1 - 1, col1, row2 - 1, col2, symbols);

    // Vérifie si l'interchange a créé au moins trois symboles identiques
    int** copy = board_copy(board, height, length);
    if (verifyInitialization(copy, height, length)) {
        canMakeAlignment(board, height, length);
        checkAndCollapse(board, height, length, &score, symbols);
        applyGravity(board, height, length);
        fillEmptySpaces(board, height, length, symbols);
        displayBoard(board, height, length, &score);
    } else {
        printf("L'interchange ne crée pas au moins trois symboles identiques. Réessayez.\n");
    }

    for (int i = 0; i < height; i++) {
        free(copy[i]);
    }
    free(copy);

    // Vérifie si un alignement est possible
    if (!canMakeAlignment(board, height, length)) {
        printf("Partie terminée ! Score final : %d\n", score);
        break; // Quitte la boucle principale pour sortir du jeu
    }
  // Propose au joueur de quitter et sauvegarder la partie
printf("Voulez-vous quitter et sauvegarder la partie ? (Appuyez sur 'S' pour sauvegarder, ou une autre touche pour continuer) : ");
char choice;
scanf(" %c", &choice);

if (choice == 'S' || choice == 's') {
            // Demande à l'utilisateur de saisir le nom de la sauvegarde
            char nomSauvegarde[100];
            printf("Nommez votre sauvegarde : ");
            scanf("%s", nomSauvegarde);

            // Sauvegarde de la partie avec le nom spécifié par l'utilisateur
            sauvegarderPartie(nomSauvegarde, height, length, symbols, score, board);
            printf("Partie sauvegardée ! Au revoir !\n");
            break;
        }

        // Continuer à jouer
        printf("Continuer la partie...\n");
    }


for (int i = 0; i < height; i++) {
    free(board[i]);
}
free(board);
    return 0;
}
