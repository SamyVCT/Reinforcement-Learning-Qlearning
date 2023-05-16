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
                while(!a_gagne(joueur_courant) && k < 4) {
                    int a = eps_greedy(action_size, epsilon, Q, s);
                    if(debug) printf("Action choisie : %d\n", a);
                    x = a / 3;
                    y = a % 3;

                    int deja_joue = jouer_coup(x, y);
                    if(deja_joue) {
                        Q[s][a] = -1000000000;
                        continue;
                    }

                    if(a_gagne(PLAYER1)) {
                        int state_board[9];
                        board_to_state(state_board);
                        int s_next;
                        s_next = search_state(state_size, state_board);

                        Q[s][a] = Q[s][a] + alpha * (100 + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                        break;
                    }

                    // Jouer un coup au hasard pour le joueur 2;
                    
                    x = rand() %3;
                    y = rand() %3;
                    while(jouer_coup(x,y)) {
                        x = rand() %3;
                        y = rand() %3;
                    }

                    if(a_gagne(PLAYER2)) {
                        int state_board[9];
                        board_to_state(state_board);
                        int s_next;
                        s_next = search_state(state_size, state_board);
                        Q[s][a] = Q[s][a] + alpha * (-100 + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                        break;
                    }

                    int state_board[9];
                    board_to_state(state_board);
                    int s_next;
                    s_next = search_state(state_size, state_board);
                    Q[s][a] = Q[s][a] + alpha * (gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                    s = s_next;

                    k++;
                }
                
                break;

            case 3 : //trading

                //on choisit un état de départ au hasard
                
                int nb_titres = rand()%2; //0 ou 1 titre possédé
                //int portefeuille = p_max;
                int done = 0;
                int stock_price = rand()%10; //indique le prix du stock, divisé en 10 intervalles
                int prix_acquisition = rand() % 10; // entre 0 et 9 pour indiquer le prix du titre possédé
                int prix_acquisition_old = prix_acquisition;

                int i = 0;
                while (done == 0 && i < 50){
                    i++;
                    int a = eps_greedy(action_size, epsilon, Q, prix_acquisition);
                    
                    //on ne peut acheter qu'un titre financier (version simple)
                    while ((nb_titres == 1 && a == 1) ||(nb_titres==0 && a == 0)){
                        a = eps_greedy(action_size, epsilon, Q, prix_acquisition);
                    }
                    if (i==1) printf("1er jour\n");
                    //printf("AVANT  = Action choisie, titre,prix_acquisition, stock,done : %d, %d, %d, %d,%d\n", a, nb_titres, prix_acquisition, stock_price,done);

                    tradeOutput stepOut = trading_step(a, prix_acquisition, prix_acquisition_old, nb_titres, stock_price);

                    int s_next = stepOut.prix_acquisition;
                    Q[prix_acquisition][a] = Q[prix_acquisition][a] + alpha * (stepOut.reward + gamma * maxVal(Q[s_next], action_size) - Q[prix_acquisition][a]);
                    
                    //on fait fluctuer le prix du stock
                    int fluctu = rand()%5 -2;// fluctuation + ou - 2
                    while( stock_price + fluctu > 9 ||  stock_price + fluctu < 0){
                        fluctu = rand()%5 -2;
                    }
                    stock_price = stock_price + fluctu; 
                    
                    prix_acquisition = s_next;
                    done = stepOut.done;
                    nb_titres = stepOut.nb_titres;
                    prix_acquisition_old = stepOut.prix_acquisition_old ;
                    //printf("APRES  = Action choisie, titre,prix_acquisition, stock,done : %d, %d, %d, %d,%d\n", a, nb_titres, prix_acquisition, stock_price,done);

                }

            break;
            default:
                printf("Jeu inconnu\n");
                exit(1);
        }

    }

    return 1;

}
