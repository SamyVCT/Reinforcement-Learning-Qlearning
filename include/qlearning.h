#ifndef QLEARNING_H
#define QLEARNING_H

#include <time.h>
#include <mazeEnv.h>
#include <functions.h>
#include <morpion.h>
#include <trading.h>


/* INPUT : jeu = 0 pour le labyrinthe, 1 pour le morpion, 2 pour le trading, nbEpisodes = nombre d'épisodes, epsilon = probabilité d'exploration, alpha = taux d'apprentissage, gamma = taux d'actualisation, Q = matrice des valeurs d'état-action, state_size = nombre d'états, action_size = nombre d'actions
 * OUTPUT : 0 si tout s'est bien passé, 1 sinon
 * DESCRIPTION : Fonction qui effectue l'apprentissage par q-renforcement sur un jeu donné
 */

int qlearning(int jeu, int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size);

#endif