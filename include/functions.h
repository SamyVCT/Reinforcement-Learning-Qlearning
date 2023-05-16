#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mazeEnv.h>

extern int min(int a, int b);

extern int max(int a, int b);

int maxInd(float* Q, int nbActions);

float maxVal(float* Q, int nbActions);

action eps_greedy(int nbActions, float eps, float** Q, int state);

int free_memory(int state_size, void** Q);


#endif
