#include <time.h>
#include <mazeEnv.h>
#include <functions.h>
#include <morpion.h>
#include <trading.h>

int qlearning(int jeu, int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size);

