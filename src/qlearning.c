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
                //int k = 0;
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
                    else {
                        // Joue un coup au hasard pour le joueur 2;
                        int a2 = rand() %9;
                        while(jouer_coup(a2)) {
                            a2 = rand() %9;
                        }

                        if(a_gagne(PLAYER2)) {
                            won = -100;
                        }
                    }

                    
                    // On met à jour la Q-table : Si l'action "a" a mené à la victoire, on augmente la récompense associée à cette action
                    // Si elle a mené à la défaite au coup au hasard suivant, on diminue la récompense associée à cette action.
                    Q[s][a] = Q[s][a] + alpha * (10+100 * won + gamma * maxVal(Q[s_next], action_size) - Q[s][a]);

                    // Met à jour l'état après que le 2e joueur a joué
                    board_to_state(state_board);
                    s = search_state(state_size, state_board);
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
                    //if (i==1) printf("1er jour\n");
                    //printf("AVANT  = Action choisie, titre,prix_acquisition, stock,done : %d, %d, %d, %d,%d\n", a, nb_titres, prix_acquisition, stock_price,done);

                    tradeOutput stepOut = trading_step(a, prix_acquisition, prix_acquisition_old, nb_titres, stock_price);

                    int s_next = stepOut.prix_acquisition;
                    
                    //on fait fluctuer le prix du stock
                    int fluctu = rand()%5 -2;// fluctuation + ou - 2
                    while( stock_price + fluctu > 9 ||  stock_price + fluctu < 0){
                        fluctu = rand()%5 -2;
                    }
                    
                    //1er chiffre de indice = stock et 2eme chiffre = acquisition
                    int indice = 10*stock_price + prix_acquisition;
                    int indice_next = 10*(stock_price + fluctu) + s_next;
                    Q[indice][a] = Q[indice][a] + alpha * (stepOut.reward + gamma * maxVal(Q[indice_next], action_size) - Q[indice][a]);
                    
                    
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
