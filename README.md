# Reinforcement Learning Project
# AUTHORS : Corentin LACHEVRE, Samy VINCENT

Voici notre dépôt github dédié à l'apprentissage par renforcement. \
On implémente différents algorithmes pour trouver la sortie d'un labyrinthe, et on les teste sur 2 autres environnements. 


Vous trouverez plusieurs dossiers : 

\data avec les fichiers textes nécessaires au fonctionnement du programme.
* maze.txt pour la résolution du labyrinthe.
* trading_day.csv pour simuler du trading avec des données réelles (disponibles sur https://finance.yahoo.com/quote/%5EFCHI?p=%5EFCHI)

\include pour les headers.

\src contient les differents algorithmes d'apprentissage par renforcement, de définition du labyrinthe et des fonctions utiles au
fontionnement du programme. 

* dfs.c est un algorithme de parcours en profondeur (non utilisé pour ce projet). 
* mazeEnv.c permet de définir le labyrinthe et d'effectuer des actions dedans. 
* functions.c contient plusieurs fonctions utiles (recherche de maximum notamment). 
* qlearning.c est un algorithme d'apprentissage par renforcement par Q-learning. 
* sarsa.c est un autre algorithme d'apprentissage par renforcement par l'algorithme de SARSA. 
* doubleqlearning.c est un algorithme d'apprentissage par renforcement par Double Q-learning. 
* main.c permet d'initialiser Q, les valeurs utiles, puis de lancer l'algorithme de renforcement choisi. 
* resolveMaze.c affiche le chemin de sortie trouvé en suivant les récompenses maximales de Q. 
* morpion.c est un jeu de morpion résolvable avec l'apprentissage par renforcement.
* trading.c permet de réaliser une étape de trading (vendre/acheter/ne rien faire) et d'afficher le comportement de l'algorithme avec des données réelles.


Pour faire fonctionner l'algorithme : 

Il faut lancer "make all" qui crée un fichier "main" à la racine du dépôt (pas dans /src !)
puis ./main <numéro algo> <nombre d'épisodes> \<epsilon\> \<alpha\> \<gamma\> \<jeu\>
* <numéro algo> = 1 pour Q-learning 
* <numéro algo> = 2 pour sarsa 
* <numéro algo> = 3 pour Double Q-learning  
* \<jeu\>  = 1 pour la résolution du labyrinthe  
* \<jeu\>  = 2 pour la résolution du morpion
* \<jeu\>  = 3 pour faire du trading \

Puis les paramètres à utiliser. \
Ces paramètres fonctionnent bien pour les trois algorithmes : 
* \<epsilon\> = 0.3
* \<alpha\> = 0.1
* \<gamma\> = 0.9

D'après nos observations, l'algorithme SARSA a besoin de plus d'épisodes pour converger : n'hésitez pas à augmenter la valeur si le labyrinthe n'est pas résolu.

INFO : \
Argent gagné au final sur 1000 entrainements avec l'algo 1 (qlearning) : 580356 \
Moyenne par entrainement : 580 \

Argent gagné au final sur 1000 entrainements avec l'algo 3 (double qlearning) : 802572 \
Moyenne par entrainement : 802