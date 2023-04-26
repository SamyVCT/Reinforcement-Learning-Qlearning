#include <qlearning.h>

int qlearning(int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size){    
    
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

        if(debug) {
            printf("Episode %d\n", i);
            printf("Position de départ : %d %d\n", state_row, state_col);
        }


        int s_terminal = 0;
        int j = 0;
        while (s_terminal==0) {
            int s = state_row * cols + state_col; //autre méthode : state_cols*rows + state_row
            action a = eps_greedy(action_size, epsilon, Q, s);
            if(debug) printf("Action choisie : %d\n", a);
            envOutput stepOut = mazeEnv_step(a);
            int s_next = stepOut.new_row * cols + stepOut.new_col;
            Q[s][a] = Q[s][a] + alpha * (stepOut.reward + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
            state_col = stepOut.new_col;
            state_row = stepOut.new_row;
            s_terminal = stepOut.done;
            j++;
        }   
    }

    return 1;

}
