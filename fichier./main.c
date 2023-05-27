int main() {
  char sauvegardes[MAX_SAUVEGARDES][100];
int nombreSauvegardes = 0;
     FILE* fichierSauvegardes;
    int choix;

    printf("\033[1;34m╔════════════════════════════════════╗\n");
    printf("║\033[1;36m      Welcome to CY Crush           \033[1;34m║\n");
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
        fichierSauvegardes = fopen("sauvegardes.txt", "r");
if (fichierSauvegardes != NULL) {
    int i = 0;
    while (fgets(sauvegardes[i], 100, fichierSauvegardes) != NULL && i < MAX_SAUVEGARDES) {
        // Supprimer le saut de ligne à la fin du nom de fichier
        sauteLigne(sauvegardes[i]);
        i++;
    }
    nombreSauvegardes = i;
    fclose(fichierSauvegardes);
}
            printf("Available backups :\n");
for (int i = 0; i < nombreSauvegardes; i++) {
    printf("%d. %s\n", i+1, sauvegardes[i]);
}
printf("Enter the number of the backup to upload: ");
int choix;
scanf("%d", &choix);

if (choix >= 1 && choix <= nombreSauvegardes) {
    char* nomSauvegarde = sauvegardes[choix-1];
    // Appeler la fonction pour charger la sauvegarde correspondante (à implémenter)
  
   
} else {
    printf("Invalid backup number.\n");
}
            break;
        case 3:
            printf("Good bye!\n");
            return 0;
        default:
            printf("Invalid option. Please choose a valid option.\n");
            return 0;
    }

    // Si l'option choisie n'est pas "Quitter", vous pouvez ajouter ici le reste du code du jeu

    int height, length, symbols;
    int score = 0;

    while (1) {
    printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
    printf("Enter the height of the grid: ");
    printf("\033[0m"); // Réinitialisation des couleurs

    char input[10];
    scanf("%s", input);

    if (strcmp(input, "E") == 0) {
        printf("Good bye!\n");
        return 0;
    }

    if (sscanf(input, "%d", &height) != 1 || height < 3 || height > 25) {
        printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
        printf("The height of the grid must be an integer between 3 and 25 inclusive. Try again.\n");
        printf("\033[0m"); // Réinitialisation des couleurs
    } else {
        break;
    }
}

while (1) {
    printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
    printf("Enter the length of the grid : ");
    printf("\033[0m"); // Réinitialisation des couleurs

    char input[10];
    scanf("%s", input);

    if (strcmp(input, "E") == 0) {
        printf("Good bye!\n");
        return 0;
    }

    if (sscanf(input, "%d", &length) != 1 || length < 3 || length > 25) {
        printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
        printf("The length of the grid must be an integer between 3 and 25 inclusive. Try again.\n");
        printf("\033[0m"); // Réinitialisation des couleurs
    } else {
        break;
    }
}


    while (1) {
        printf("\033[1;33m"); // Couleur jaune vif pour les phrases d'invitation
        printf("Enter the number of symbols (between 4 and 6) : ");
        printf("\033[0m"); // Réinitialisation des couleurs

        char input[10];
        scanf("%s", input);

        if (strcmp(input, "E") == 0) {
            printf("Good bye !\n");
            return 0;
        }

        if (sscanf(input, "%d", &symbols) != 1 || symbols < 4 || symbols > 6) {
            printf("\033[1;31m"); // Couleur rouge vif pour les messages d'erreur
            printf("The number of symbols must be an integer between 4 and 6. Try again.\n");
            printf("\033[0m"); // Réinitialisation des couleurs
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
// Après l'appel à boardInitializer
checkSymbolsAdjacent(board, height, length, symbols);

displayBoard(board, height, length, &score);

    while (1) {
    int row1, col1, row2, col2;

    printf("Choose the coordinates of the first symbol to interchange (number letter) : ");
    char column1;
    char input1[100];
    scanf("%s", input1);

    if (strcmp(input1, "E") == 0 || strcmp(input1, "e") == 0) {
        printf("Good bye !\n");
        break;
    }
    if (strcmp(input1, "S") == 0 || strcmp(input1, "s") == 0) {
        printf("Backup Name : ");
        char saveName[100];
        scanf("%s", saveName);
        sauvegarderPartie(saveName, height, length, symbols, score, board);

        printf("Backup added : %s\n", saveName);
        strcpy(sauvegardes[nombreSauvegardes], saveName);
nombreSauvegardes++;
FILE* fichierSauvegardes = fopen("sauvegardes.txt", "a");
if (fichierSauvegardes != NULL) {
    fprintf(fichierSauvegardes, "%s\n", saveName);
    fclose(fichierSauvegardes);
        // Effectuer la sauvegarde de partie avec saveName
        continue;
    }
    }

    if (sscanf(input1, " %c%d", &column1, &row1) != 2 || row1 < 1 || row1 > height || column1 < 'A' || column1 > 'A' + length) {
        printf("Invalid contact information. Try again.\n");
        continue;
    }
    col1 = column1 - 'A';

    printf("Choose the coordinates of the second symbol to interchange (number letter): ");
    char column2;
    char input2[100];
    scanf("%s", input2);

    if (strcmp(input2, "E") == 0 || strcmp(input2, "e") == 0) {
        printf("Good bye !\n");
        break;
    }
    if (strcmp(input2, "S") == 0 || strcmp(input2, "s") == 0) {
        printf("Backup Name : ");
        char saveName[100];
        scanf("%s", saveName);
        sauvegarderPartie(saveName, height, length, symbols, score, board);

        printf("Backup added : %s\n", saveName);
        strcpy(sauvegardes[nombreSauvegardes], saveName);
nombreSauvegardes++;
FILE* fichierSauvegardes = fopen("sauvegardes.txt", "a");
if (fichierSauvegardes != NULL) {
    fprintf(fichierSauvegardes, "%s\n", saveName);
    fclose(fichierSauvegardes);
        // Effectuer la sauvegarde de partie avec saveName
        continue;
    }
    }

    if (sscanf(input2, " %c%d", &column2, &row2) != 2 || row2 < 1 || row2 > height || column2 < 'A' || column2 > 'A' + length) {
        printf("Invalid contact information. Try again.\n");
        continue;
    }
    col2 = column2 - 'A';



    // Interchange les symboles sélectionnés
    swapSymbols(board, height, length, score, row1 - 1, col1, row2 - 1, col2, symbols);

    // Vérifie si l'interchange a créé au moins trois symboles identiques
    int** copy = board_copy(board, height, length);
if (verifyInitialization(copy, height, length)) {
    if (canMakeAlignment(board, height, length)) {
        checkAndCollapse(board, height, length, &score, symbols);
        applyGravity(board, height, length);
        fillEmptySpaces(board, height, length, symbols);
        displayBoard(board, height, length, &score);
    } else {
        printf("Interchange does not create at least three identical symbols. Try again.\n");
    }
} 

    for (int i = 0; i < height; i++) {
        free(copy[i]);
    }
    free(copy);

    // Vérifie si un alignement est possible
    if (!canMakeAlignment(board, height, length)) {
        printf("Game over! Final score : %d\n", score);
        break; // Quitte la boucle principale pour sortir du jeu
    }
}

for (int i = 0; i < height; i++) {
    free(board[i]);
}
free(board);
    return 0;
}
