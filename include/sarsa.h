#include <time.h>
#include <mazeEnv.h>
#include <functions.h>


int sarsa(int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size);
