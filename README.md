# Reinforcement Learning Project : Maze 

Voici notre dépôt github dédié à l'apprentissage par renforcement.
On implémente différents algorithmes pour trouver la sortie d'un labyrinthe.

Vous trouverez plusieurs dossiers :

/Include pour les headers

/src contient les algorithmes d'apprentissage par renforcement et de définition du labyrinthe.

dfs.c est un algorithme de parcours en profondeur (non utilisé pour ce projet).

mazeEnv.c permet de définir le labyrinthe et d'effectuer des actions dedans.

functions.c contient des plusieurs fonctions utiles.

algo1.c est un algorithme de Q-learning et epsilon greedy.

max.c permet de renvoyer la valeur maximale et son indice dans un tableau.

main.c permet d'initialiser Q, les valeurs utiles, puis de lancer l'algorithme de renforcement choisi.

Pour faire fonctionner l'algorithme : 
Il faut lancer make qui crée un fichier "main" à la racine du dépôt (pas dans /src !)
puis ./main <numéro algo> <nombre d'épisodes> <epsilon> <alpha> <gamma>
en spécifiant <numéro algo> = 1 pour Q-learning
puis les paramètres à utiliser.

