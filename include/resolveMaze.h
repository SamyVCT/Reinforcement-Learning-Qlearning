#ifndef RESOLVEMAZE_H
#define RESOLVEMAZE_H

#include <mazeEnv.h>
#include <stdio.h>
#include <functions.h>

// INPUT : Q : tableau contenant les valeurs de la fonction Q après entrainement, action_size : nombre d'actions possibles, path : tableau contenant le chemin trouvé, path_size : taille du chemin trouvé
// OUTPUT : 1 (et modifie path et path_size)
// DESCRIPTION : Fonction qui résout le labyrinthe à partir de la matrice Q
int resolveMaze(float** Q, int action_size, action* path, int* path_size);


// INPUT : chemin "path" et sa taille "path_size" 
// OUTPUT : 1 et affiche le chemin
int showResult(action* path, int path_size);

#endif