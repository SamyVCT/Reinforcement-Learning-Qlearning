#include <mazeEnv.h>

void algo1(int nbEpisodes,double epsilon,double alpha, double gamma, int **Q, int state_size, int action_size){    
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