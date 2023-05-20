#include "functions.h"

int min(int a, int b){
    return (a>b) ? b : a;
}

int max(int a, int b){
    return (a>b) ? a : b;
}

int maxInd(float* Q, int nbActions) {
    int maxi = 0;
    int random = rand() % 9;
    for (int i = 1; i < nbActions; i++) {
        if (Q[i] > Q[maxi]) {
            maxi = i;
        }
        else if(i < random && Q[i] == Q[maxi]){
            maxi = i;
        }
    }
    return maxi;
}

// Prend un tableau Q de taille nbActions en entrée et renvoie la plus grande valeur
float maxVal(float* Q, int nbActions) {
    float maxi = -1000000000;
    for (int i = 0; i < nbActions; i++) {
        if (Q[i] > maxi) {
            maxi = Q[i];
        }
    }
    return maxi;
}

// Prend en argument la matrice des récompenses Q, l'état actuel state et le nombre d'actions possibles nbActions et renvoie l'action qui maximise Q
// avec une probabilité 1-eps et une action aléatoire avec une probabilité eps
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

// libère la mémoire de la matrice Q de "state_size" lignes.
int free_memory(int lines, void** Q) {
    for (int i = 0; i < lines; i++) {
        free(Q[i]);
    }
    free(Q);
    return 0;
}