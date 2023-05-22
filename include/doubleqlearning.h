#ifndef DOUBLEQLEARNING_H
#define DOUBLEQLEARNING_H

#include <functions.h>
#include <time.h>


/* INPUT : jeu = 0 pour le labyrinthe, 1 pour le morpion, 2 pour le trading, nbEpisodes = nombre d'épisodes, epsilon = probabilité d'exploration, alpha = taux d'apprentissage, gamma = taux d'actualisation, 
 * OUTPUT : 0 si tout s'est bien passé, 1 sinon
 * DESCRIPTION : Fonction qui effectue l'apprentissage par double q-renforcement sur un jeu donné
 */
int doubleqlearning(int jeu, int nbEpisodes,double epsilon,double alpha, double gamma, float **Q1, float **Q2, int state_size, int action_size);

#endif