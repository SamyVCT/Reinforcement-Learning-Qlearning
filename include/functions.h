#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mazeEnv.h>

/* INPUT : a et b deux entiers
 * OUTPUT : le minimum entre a et b
 * DESCRIPTION : Fonction qui renvoie le minimum entre a et b
 */
extern int min(int a, int b);

/* INPUT : a et b deux entiers
 * OUTPUT : le maximum entre a et b
 * DESCRIPTION : Fonction qui renvoie le maximum entre a et b
 */
extern int max(int a, int b);

/* INPUT : Q : tableau (à une ligne), de taille nbActions.
 * OUTPUT : indice de la plus grande valeur de Q
 * DESCRIPTION : Fonction qui renvoie l'indice de la plus grande valeur de Q
 */
int maxInd(float* Q, int nbActions);

/* INPUT : Q : tableau (à une ligne), de taille nbActions.
 * OUTPUT : Plus grande valeur de Q
 * DESCRIPTION : Fonction qui renvoie la plus grande valeur de Q
 */
float maxVal(float* Q, int nbActions);

/* INPUT : Q : Matrice des états et des actions, state : état actuel, nbActions : nombre d'actions possibles, eps : probabilité d'exploration
 * OUTPUT : action à effectuer
 * DESCRIPTION : Fonction qui renvoie l'action à effectuer en suivant la politique epsilon-greedy
 */
action eps_greedy(int nbActions, float eps, float** Q, int state);

/* INPUT : Q : Matrice de type générique, lines : nombre de lignes
 * OUTPUT : 0
 * DESCRIPTION : Libère la mémoire allouée à Q
 */
int free_memory(int lines, void** Q);

#endif
