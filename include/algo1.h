#include <time.h>
#include <mazeEnv.h>
#include <max.h>



int algo1(int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size);

action eps_greedy(int nbActions, float eps, float** Q, int state);
