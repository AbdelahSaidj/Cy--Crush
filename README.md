# Cy--Crush
ReadMe CyCrush 

 

CyCrush est un jeu de puzzle inspiré du célèbre CandyCrush dans lequel vous devez aligner des symboles identiques pour les faire disparaître et marquer des points. Le jeu est écrit en langage C et utilise la bibliothèque standard. 

 

Compilation 

Pour compiler le jeu, vous devez disposer d'un compilateur C (par exemple, GCC,replit github) installé sur votre système. 

 

Exécution 
Une fois le jeu compilé, vous pouvez l'exécuter en lançant le fichier exécutable généré.sh 

Règles du jeu 

Au début du jeu, une grille de symboles est générée. 
Vous pouvez déplacer un symbole à la fois pour créer des alignements horizontaux ou verticaux d'au moins trois symboles identiques. 
Lorsqu'un alignement est réalisé, les symboles disparaissent et vous marquez des points. 
Après chaque coup, de nouveaux symboles apparaissent pour combler les espaces vides. 
Le jeu se termine lorsque vous ne pouvez plus faire d'alignements. 
Votre objectif est de marquer le maximum de points possible. 
Vous pouvez quitter la partie en entrant la touche “E” et cela en plein jeu. 
Vous pouvez sauvegarder la partie en entrant la touche “S” et cela en plein jeu. 

 

Commandes 

Utilisez les lettres A, B, C, ... pour sélectionner la colonne où se trouve le symbole que vous souhaitez déplacer. 

Utilisez les chiffres 1, 2, 3, ... pour sélectionner la ligne où se trouve le symbole que vous souhaitez déplacer. 

Appuyez sur la touche Enter pour valider votre mouvement. 

 

Fonctions principales 
displayBoard: Affiche la grille de jeu avec les symboles et le score actuel. 
displayRandomPhrase: Affiche une phrase aléatoire de félicitations après un bon coup. 
verifyInitialization: Vérifie si la grille de jeu est correctement initialisée. 
board_copy: Effectue une copie de la grille de jeu. 
applyGravity: Applique la gravité pour diriger les symboles vers la droite dans les espaces vides. 
fillEmptySpaces: Remplit les espaces vides avec de nouveaux symboles aléatoires. 
boardInitializer: Initialise la grille de jeu avec des symboles aléatoires. 
checkSymbolsAdjacent: Vérifie et supprime les alignements de symboles adjacents. 
canMakeAlignment: Vérifie si un alignement d'au moins trois symboles est possible. 
checkAndCollapse: Vérifie et supprime les alignements de symboles, en les remplaçant par des zéros. 

 

Bugs 

Message d’erreur lors du chargement d’une partie sauvegardée. 

 

 


N'hésitez pas à explorer le code pour en savoir plus sur son fonctionnement. 
Bonne chance et amusez-vous bien en jouant à CyCrush ! 
