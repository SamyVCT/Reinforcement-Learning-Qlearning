#include <qlearning.h>

int qlearning(int jeu, int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size){    
    
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

        switch(jeu) {
            case 1: // Maze
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
                break;
            case 2: // Morpion
                
                // On choisit un état de départ au hasard

                int s = 0;
                int k = 0;
                int x;
                int y;
                init_plateau();
                while(!a_gagne(joueur_courant) && k < 9) {
                    action a = eps_greedy(action_size, epsilon, Q, s);
                    if(debug) printf("Action choisie : %d\n", a);
                    x = a / 3;
                    y = a % 3;

                    jouer_coup(x, y);

                    if(a_gagne(PLAYER1)) {
                        int state_board[9];
                        board_to_state(state_board);
                        int s_next;
                        s_next = search_state(Q, state_size, state_board);

                        Q[s][a] = Q[s][a] + alpha * (100 + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                        break;
                    }

                    // Jouer un coup au hasard pour le joueur 2;
                    
                    x = rand()%3;
                    y = rand()%3;
                    while(jouer_coup(x,y)) {
                        x = rand()%3;
                        y = rand()%3;
                    }

                    if(a_gagne(PLAYER2)) {
                        int state_board[9];
                        board_to_state(state_board);
                        int s_next;
                        s_next = search_state(Q, state_size, state_board);

                        Q[s][a] = Q[s][a] + alpha * (-100 + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                        break;
                    }

                    int state_board[9];
                    board_to_state(state_board);
                    int s_next;
                    s_next = search_state(Q, state_size, state_board);
                    
                    Q[s][a] = Q[s][a] + alpha * (gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                    s = s_next;

                    k++;
                }
                




                break;
            default:
                printf("Jeu inconnu\n");
                exit(1);
        }

    }

    return 1;

}
