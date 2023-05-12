#include <qlearning.h>

int qlearning(int jeu, int nbEpisodes,double epsilon,double alpha, double gamma, float **Q, int state_size, int action_size){    
    
    /* 
     Fonctionnement de l'algo
     initialisation :
     Q(s,a) dans R, si s terminal Q(s,a) = 0
     entrainement :
     foreach episode : initialise s, 
     repeat foreach step
     a <- chose action (s,Q)
     take action
     observe s', r
     formule ...
     s <- s'
     unitl s is terminal 
     */
    
    srand(time(NULL));
    
    for (int i = 0; i<= nbEpisodes;i++){

        switch(jeu) {

            // ################ Labyrinthe ################
            case 1: 
                //mazeEnv_reset(); 

                // On choisi une position de départ au hasard

                state_col = rand() % cols;
                state_row = rand() % rows;

                // On vérifie que la position choisie est valide

                while (mazeEnv_is_wall(state_row, state_col)){
                    state_col = rand() % cols;
                    state_row = rand() % rows;
                }

                #ifdef DEBUG
                    printf("Episode %d\n", i);
                    printf("Position de départ : %d %d\n", state_row, state_col);
                #endif              
                
                // On lance l'épisode de l'algorithme
                int s_terminal = 0;
                while (s_terminal==0) {
                    int s = state_row * cols + state_col; 
                    action a = eps_greedy(action_size, epsilon, Q, s);
                    #ifdef DEBUG
                        printf("Action choisie : %d\n", a);
                    #endif

                    envOutput stepOut = mazeEnv_step(a); // effectue le déplacement dans le labyrinth et renvoie le nouvel état, la récompense et si l'état est terminal
                    int s_next = stepOut.new_row * cols + stepOut.new_col;
                    Q[s][a] = Q[s][a] + alpha * (stepOut.reward + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                    state_col = stepOut.new_col;
                    state_row = stepOut.new_row;
                    s_terminal = stepOut.done;
                }  
                break;

            // ################ Morpion ################
            case 2:
                
                // On choisi un état de départ au hasard

                int s = 0;
                int k = 0;
                int won = 0;
                init_plateau();
                
                while(!a_gagne(joueur_courant) && nb_coups < 8) {
                    int a = eps_greedy(action_size, epsilon, Q, s);
                    #ifdef DEBUG
                        printf("Action choisie : %d\n", a);
                    #endif

                    int deja_joue = jouer_coup(a); // 1 si le coup a déjà été joué, 0 sinon (cette fonction joue le coup si il est valide)

                    // Si le coup était invalide, on baisse la récompense associée à cette action
                    if(deja_joue) {
                        Q[s][a] = -1000000000;
                        continue;
                    }


                    // On récupère le state lié au plateau actuel (après avoir joué le coup) -> cf fonctions board_to_state et search_state
                    int state_board[9];
                    board_to_state(state_board);
                    int s_next;
                    s_next = search_state(state_size, state_board);

                    if(a_gagne(PLAYER1)) {
                        won = 1;
                    }

                    // Joue un coup au hasard pour le joueur 2;
                    int a2 = rand() %9;
                    while(jouer_coup(a2)) {
                        a2 = rand() %9;
                    }

                    if(a_gagne(PLAYER2)) {
                        won = -1;
                    }
                    
                    // On met à jour la Q-table : Si l'action "a" a mené à la victoire, on augmente la récompense associée à cette action
                    // Si elle a mené à la défaite au coup au hasard suivant, on diminue la récompense associée à cette action.
                    Q[s][a] = Q[s][a] + alpha * (100 * won + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                    s = s_next;

                }
                
                break;

            // ################ Trading ################
            case 3:
                //on choisi un état de départ au hasard
                
                int nb_titres = 0;
                //int portefeuille = p_max;
                int done = 0;
                int stock_price = rand()%10; //indique le prix du stock, divisé en 10 intervalles
                int s = rand() % 11; // entre 0 et 9 pour indiquer le prix du titre possédé, 10 : aucun titre possédé
                int prix_achat ;
                
                init_trading();

                while (done == 0){
                    
                    int a = eps_greedy(action_size, epsilon, Q, s);
                    
                    //on ne peut acheter qu'un titre financier
                    while ((nb_titres == 1 && a == buy) ||(nb_titres==0 && a == sell)){
                        a = eps_greedy(action_size, epsilon, Q, s);
                    }

                    #ifdef DEBUG
                            printf("Action choisie : %d\n", a);
                        #endif

                    tradeOutput stepOut = trading_step(a);
                    int s_next = stepOut.new_state;
                    Q[s][a] = Q[s][a] + alpha * (stepOut.reward + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);
                    
                    //on fait fluctuer le prix du stock
                    int fluctu = rand()%5 -2;// fluctuation + ou x- 2
                    while( stock_price + fluctu > p_max ||  stock_price + fluctu < p_min){
                        fluctu = rand()%5 -2;
                    }
                    stock_price = stock_price + fluctu; 
                    
                    s = s_next;
                    prix_achat = stepOut.prix_achat;
                    done = stepOut.done;
                    nb_titres = stepOut.nb_titres;
                }

                break;

            default:
                printf("Jeu inconnu\n");
                exit(1);
        }

    }

    return 1;

}
