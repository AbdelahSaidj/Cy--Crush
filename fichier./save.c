#include "header.h"

void sauvegarderPartie(const char* nomFichier, int hauteur, int longueur, int symboles, int score, int** board) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        // Écriture des informations de la partie
        if (fprintf(fichier, "%d\n%d\n%d\n%d\n", hauteur, longueur, symboles, score) < 0) {
            printf("Error writing to backup file.\n");
            fclose(fichier);
            return;
        }

        // Écriture de l'état du board
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < longueur; j++) {
                fprintf(fichier, "%d ", board[i][j]);
            }
            fprintf(fichier, "\n");
        }

        fclose(fichier);
        printf("Successfully saved game.\n");
    } else {
        printf("Error opening backup file.\n");
    }
}

int chargerPartie(const char* nomFichier, int*** board, int* hauteur, int* longueur, int* symboles, int* score) {
    FILE* fichierSauvegarde = fopen(nomFichier, "r");
    if (fichierSauvegarde == NULL) {
        printf("Erreur : Unable to open backup file.\n");
        return 0; // Échec du chargement de la partie
    }

    // Lire les données de la sauvegarde à partir du fichier
    // Assurez-vous que le format de la sauvegarde correspond à la structure de données utilisée dans le jeu
    // et effectuez les opérations nécessaires pour charger les valeurs correctement

    // Exemple de lecture d'une sauvegarde :
    fscanf(fichierSauvegarde, "%d %d %d %d", hauteur, longueur, symboles, score);

    // Allouer l'espace mémoire pour le tableau de jeu
    *board = (int**)malloc((*hauteur) * sizeof(int*));
    for (int i = 0; i < *hauteur; i++) {
        (*board)[i] = (int*)malloc((*longueur) * sizeof(int));
    }

    // Lire les valeurs du tableau de jeu à partir de la sauvegarde
    for (int i = 0; i < *hauteur; i++) {
        for (int j = 0; j < *longueur; j++) {
            fscanf(fichierSauvegarde, "%d", &((*board)[i][j]));
        }
    }

    fclose(fichierSauvegarde);
    return 1; // Chargement de la partie réussi
}


void sauteLigne(char* chaine) {
    int longueur = strlen(chaine);

    // Parcourir la chaîne jusqu'au saut de ligne ou la fin de la chaîne
    for (int i = 0; i < longueur; i++) {
        if (chaine[i] == '\n') {
            chaine[i] = '\0'; // Remplacer le saut de ligne par le caractère nul pour terminer la chaîne
            break;
        }
    }
}
