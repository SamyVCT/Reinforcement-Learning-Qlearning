#ifndef SARSA_H
#define SARSA_H

#include <time.h>
#include <mazeEnv.h>
#include <functions.h>

/* INPUT : nbEpisodes = nombre d'épisodes, epsilon = probabilité d'exploration, alpha = taux d'apprentissage, gamma = taux d'actualisation, Q = matrice des valeurs d'état-action, state_size = nombre d'états, action_size = nombre d'actions
 * OUTPUT : 0 si tout s'est bien passé, 1 sinon
 * DESCRIPTION : Fonction qui effectue l'apprentissage par renforcement avec l'algorithme SARSA (uniquement pour le labyrinthe)
 */
int sarsa(int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size);

#endif