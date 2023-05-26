#include "header.h"

void sauvegarderPartie(const char* nomFichier, int hauteur, int longueur, int symboles, int score, int** plateau) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier != NULL) {
        fprintf(fichier, "%d\n%d\n%d\n%d\n", hauteur, longueur, symboles, score);
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < longueur; j++) {
                fprintf(fichier, "%d ", plateau[i][j]);
            }
            fprintf(fichier, "\n");
        }
        fclose(fichier);
        printf("Partie sauvegardée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    }
}

void chargerPartie(const char* nomFichier, int* hauteur, int* longueur, int* symboles, int* score, int*** plateau) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        if (fscanf(fichier, "%d\n%d\n%d\n%d\n", hauteur, longueur, symboles, score) != 4) {
            printf("Erreur lors de la lecture du fichier de sauvegarde.\n");
        } else {
            // Allouer de la mémoire pour le plateau de jeu
            *plateau = malloc(*hauteur * sizeof(int*));
            for (int i = 0; i < *hauteur; i++) {
                (*plateau)[i] = malloc(*longueur * sizeof(int));
            }

            // Charger l'état du plateau de jeu
            for (int i = 0; i < *hauteur; i++) {
                for (int j = 0; j < *longueur; j++) {
                    if (fscanf(fichier, "%d", &(*plateau)[i][j]) != 1) {
                        printf("Erreur lors de la lecture du fichier de sauvegarde.\n");
                        // Libérer la mémoire allouée pour le plateau de jeu
                        for (int k = 0; k < i; k++) {
                            free((*plateau)[k]);
                        }
                        free(*plateau);
                        *plateau = NULL;
                        fclose(fichier);
                        return;
                    }
                }
            }

            fclose(fichier);
            printf("Partie chargée avec succès.\n");
        }
    } else {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
    }
}

void obtenirCheminSauvegarde(char* chemin) {
    const char* dossierSauvegarde = "sauvegardes";
    const char* repertoireUtilisateur = getenv("HOME");

    if (repertoireUtilisateur == NULL) {
        printf("Impossible de trouver le répertoire de l'utilisateur.\n");
        exit(1);
    }

    snprintf(chemin, 100, "%s/%s", repertoireUtilisateur, dossierSauvegarde);
}

void afficherSauvegardes() {
    char chemin[100];
    obtenirCheminSauvegarde(chemin);

    DIR *directory;
    struct dirent *file;

    directory = opendir(chemin);

     if (directory) {
        int count = 1;
        bool sauvegardesTrouvees = false; // Variable pour suivre si des sauvegardes ont été trouvées

        printf("Liste des sauvegardes :\n");

        while ((file = readdir(directory)) != NULL) {
            if (file->d_type == DT_REG) { // Filtre les fichiers réguliers (sauvegardes)
                printf("%d. %s\n", count, file->d_name);
                count++;
                sauvegardesTrouvees = true;
            }
        }

        closedir(directory);

        if (!sauvegardesTrouvees) {
            printf("Aucune sauvegarde trouvée.\n");
        }
    } else {
        printf("Erreur lors de l'ouverture du dossier de sauvegarde.\n");
       exit(EXIT_FAILURE); // Quitte le programme avec un code d'erreur
    }
}


char nomSauvegarde[100];
