#include "functions.h"

int min(int a, int b){
    return (a>b) ? b : a;
}

int max(int a, int b){
    return (a>b) ? a : b;
}


int maxInd(float* Q, int nbActions) {
    int maxi = 0;
    for (int i = 1; i < nbActions; i++) {
        if (Q[i] > Q[maxi]) {
            maxi = i;
        }
        if(Q[i] == Q[maxi]){
            int random = rand() % 2;
            if(random == 1){
                maxi = i;
            }
        }
    }
    return maxi;
}

float maxVal(float* Q, int nbActions) {
    float maxi = -1000000000;
    for (int i = 0; i < nbActions; i++) {
        if (Q[i] > maxi) {
            maxi = Q[i];
        }
    }
    return maxi;
}


action eps_greedy(int nbActions, float eps, float** Q, int state){
    int action;
    double random = (double)rand() / (double)RAND_MAX;
    if (random < eps){
        int act = rand() % nbActions;
        action = act; // Choisir une action au hasard
    }else{
        action = maxInd(Q[state], nbActions); // Choisir l'action qui maximise Q
    }
    return action;
}