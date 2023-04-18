#include <mazeEnv.h>

void algo1(int nbEpisodes){
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
   
    double alpha = 0.1;// taux d'apprentissage entre 0 et 1
    double epsilon  = 0.1; // strict. positif
    
    // Fonctionnement de l'algo
    //initialisation :
    // Q(s,a) dans R, si s terminal Q(s,a) = 0
    // entrainement :
    // foreach episode : initialise s, 
    // repeat foreach step
    // a <- chose action (s,Q)
    // take action
    // observe s', r
    // formule ...
    // s <- s'
    // unitl s is terminal
    
    //int* current = &visited[row][col];

    action a;
    for (int i; i<= nbEpisodes;i++){
        //choose start
        mazeEnv_reset(); 
        int s_terminal = 0;
        while (s_terminal==0) {
            int s = state_row * cols + state_col //autre méthode : state_cols*rows + state_row
            action a = eps_greedy(nbActions, eps, Q, s);
            envOutput stepOut = mazeEnv_step(a);
            int s_next = stepOut.state_row * cols + stepOut.state_col;

            Q[s][a] = Q[s][a] + alpha * (stepOut.reward + gamma * argmax(Q[s_next]) — Q[s][a])
            state_col = stepOut.state_col;
            state_row = stepOut.state_row;
            s_terminal = envOutput.done;
        }   
    }



}

action eps_greedy(int nbActions, float eps, int** Q, int state){
    int action;
    if (rand() < eps){
        action = rand() % nbActions; // Choisir une action au hasard
    }else{
        action = argmax(Q[state]); // Choisir l'action qui maximise Q
    }
    return action;
}
//calcule max


