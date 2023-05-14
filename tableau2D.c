#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour générer un nombre aléatoire entre min et max
int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Fonction pour afficher la grille
void afficherGrille(char** grille, int taille) {
    printf("\n");
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            printf("%c ", grille[i][j]);
        }
        printf("\n");
    }
}

// Fonction pour vérifier si trois symboles identiques sont alignés horizontalement ou verticalement
int verifierAlignement(char** grille, int taille, int nombreSymboles) {
    // Vérification horizontale
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille - 2; j++) {
            if (grille[i][j] == grille[i][j + 1] && grille[i][j] == grille[i][j + 2]) {
                return 1;
            }
        }
    }

    // Vérification verticale
    for (int i = 0; i < taille - 2; i++) {
        for (int j = 0; j < taille; j++) {
            if (grille[i][j] == grille[i + 1][j] && grille[i][j] == grille[i + 2][j]) {
                return 1;
            }
        }
    }

    return 0;
}

// Fonction pour échanger deux symboles dans la grille
void echangerSymboles(char** grille, int row1, int col1, int row2, int col2) {
    char temp = grille[row1][col1];
    grille[row1][col1] = grille[row2][col2];
    grille[row2][col2] = temp;
}

int main() {
    int tailleGrille, nombreSymboles;

    // Demande à l'utilisateur la taille de la grille
    printf("Entrez la taille de la grille : ");
    scanf("%d", &tailleGrille);

    // Demande à l'utilisateur le nombre de symboles
    printf("Entrez le nombre de symboles (entre 4 et 6) : ");
    scanf("%d", &nombreSymboles);

    if (nombreSymboles < 4 || nombreSymboles > 6) {
        printf("Le nombre de symboles doit être entre 4 et 6.\n");
        return 1;
    }

    // Allocation dynamique de la grille
    char** grille = (char**)malloc(tailleGrille * sizeof(char*));
    for (int i = 0; i < tailleGrille; i++) {
        grille[i] = (char*)malloc(tailleGrille * sizeof(char));
    }

    // Génération de la grille aléatoire
    srand(time(NULL));
    for (int i = 0; i < tailleGrille; i++) {
        for (int j = 0; j < tailleGrille; j++) {
            grille[i][j] = 'A' + randomInt(0, nombreSymboles - 1);
        }
    }

    // Boucle
int ligne1, colonne1, ligne2, colonne2;
char reponse;

do {
    // Affichage de la grille
    afficherGrille(grille, tailleGrille);

    // Demande à l'utilisateur les positions des symboles à échanger
    printf("Entrez les coordonnées du premier symbole (ligne colonne) : ");
    scanf("%d %d", &ligne1, &colonne1);
    printf("Entrez les coordonnées du deuxième symbole (ligne colonne) : ");
    scanf("%d %d", &ligne2, &colonne2);

    // Vérification des coordonnées saisies
    if (ligne1 < 0 || ligne1 >= tailleGrille || colonne1 < 0 || colonne1 >= tailleGrille ||
        ligne2 < 0 || ligne2 >= tailleGrille || colonne2 < 0 || colonne2 >= tailleGrille) {
        printf("Coordonnées invalides. Veuillez réessayer.\n");
        continue;
    }

    // Échange des symboles dans la grille
    echangerSymboles(grille, ligne1, colonne1, ligne2, colonne2);

    // Vérification des alignements après l'échange
    if (verifierAlignement(grille, tailleGrille, nombreSymboles)) {
        printf("Alignement trouvé !\n");
        break;
    }

    // Demande à l'utilisateur s'il souhaite continuer à jouer
    printf("Voulez-vous continuer à jouer ? (O/N) : ");
    scanf(" %c", &reponse);
} while (reponse == 'O' || reponse == 'o');

// Libération de la mémoire
for (int i = 0; i < tailleGrille; i++) {
    free(grille[i]);
}
free(grille);

return 0;
}
