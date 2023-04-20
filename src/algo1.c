#include <mazeEnv.h>
#include <algo1.h>

int algo1(int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size){    
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
            int s = state_row * cols + state_col; //autre méthode : state_cols*rows + state_row
            action a = eps_greedy(action_size, epsilon, Q, s);
            envOutput stepOut = mazeEnv_step(a);
            int s_next = stepOut.new_row * cols + stepOut.new_col;

            Q[s][a] = Q[s][a] + alpha * (stepOut.reward + gamma * max(Q[s_next], action_size) - Q[s][a]);
            state_col = stepOut.new_col;
            state_row = stepOut.new_row;
            s_terminal = stepOut.done;
        }   
    }

    return 0;

}

action eps_greedy(int nbActions, float eps, float** Q, int state){
    int action;
    if (rand() < eps){
        action = rand() % nbActions; // Choisir une action au hasard
    }else{
        action = max(Q[state], nbActions); // Choisir l'action qui maximise Q
    }
    return action;
}