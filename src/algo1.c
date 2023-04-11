#include <mazeEnv.h>

void algo1(){
    int action_size = numer_of_actions;
    int state_size = rows*cols; 
   
    //on met les états sur les lignes et les actions possibles sur les colonnes
    int **Q = (int **)malloc(state_size * sizeof(int*));
    for(int i = 0; i < state_size; i++) Q[i] = (int *)malloc(action_size * sizeof(int));
    
    //Initialisation de Q
    for(int i = 0; i < state_size; i++){
        for(int j = 0; j < action_size; j++){
            Q[i][j] = 0;

        }
    }

    // autre def de Q ? int *Q = (int *)malloc(state_size * action_size * sizeof(int));
   
    double alpha = 0.2;// taux d'apprentissage entre 0 et 1

    int episode = 10;
    for (int i; i<= episode;i++){
        //choose start
        action a = 
    }

    Q[state][action] = Q[state][action] + alpha * (reward + gamma * argmax(Q[New_state]) — Q[state][action])


}

action esp_greedy(int nbActions, float eps, int** Q, int state){
    int action;
    if (rand() < eps){
        action = rand() % nbActions; // Choisir une action au hasard
    }else{
        action = argmax(Q[state]); // Choisir l'action qui maximise Q
    }
    return action;
}
//calcule max
