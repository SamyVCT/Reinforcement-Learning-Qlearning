#include <mazeEnv.h>
#include <sarsa.h>

int sarsa(int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size){    
    
    // Fonctionnement de l'algo
    //initialisation :
    // Q(s,a) dans R, si s terminal Q(s,a) = 0
    // entrainement :
    // foreach episode : initialise s, 
    // a <- chose action (s,Q)
    // repeat foreach step
    // take action
    // observe s', r
    //Etape supplémentaire par rapport à algo1 : choisir une action a' depuis s' en utilisant la politique spécifiée par Q
    // formule légèrement différente ...
    // s <- s'
    // unitl s is terminal
    srand(time(NULL));
    
    for (int i = 0; i<= nbEpisodes;i++){
        //mazeEnv_reset(); 

        // On choisit une position de départ au hasard

        state_col = rand() % cols;
        state_row = rand() % rows;

        // On vérifie que la position choisie est valide

        while (mazeEnv_is_wall(state_row, state_col)){
            state_col = rand() % cols;
            state_row = rand() % rows;
        }

        int s_terminal = 0;
        int j = 0;

        int s = state_row * cols + state_col; //autre méthode : state_cols*rows + state_row
        action a = eps_greedy(action_size, epsilon, Q, s);

        while (s_terminal==0) {
            
            envOutput stepOut = mazeEnv_step(a);
            int s_next = stepOut.new_row * cols + stepOut.new_col;

            action aprime = eps_greedy(action_size, epsilon, Q, s_next);


            Q[s][a] = Q[s][a] + alpha * (stepOut.reward + gamma * Q[s_next][aprime] - Q[s][a]);
            state_col = stepOut.new_col;
            state_row = stepOut.new_row;
            s_terminal = stepOut.done;

            a = aprime;
            s = s_next;

            j++;
        }   
    }

    return 1;

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