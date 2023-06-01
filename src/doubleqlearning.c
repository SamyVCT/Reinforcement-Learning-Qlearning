#include <doubleqlearning.h>
#include <trading.h>

int doubleqlearning(int jeu, int nbEpisodes,double epsilon,double alpha, double gamma, float **Q1, float **Q2, int state_size, int action_size){    
    
    /* 
     Fonctionnement de l'algo
     initialisation :
     Q(s,a) dans R, si s terminal Q(s,a) = 0
     entrainement :
     foreach episode : initialise s, 
     repeat foreach step
     a <- chose action (s,Q1+Q2)
     take action
     observe s', r
     formule sur Q1 ou Q2 (avec proba 0.5)
     s <- s'
     unitl s is terminal 
     */

    
        //creation de Q pour la recherche epsilon-greedy
        float **Q = (float **)malloc(state_size * sizeof(float*));
            for(int i = 0; i < state_size; i++) Q[i] = (float *)malloc(action_size * sizeof(float));
        if (Q == NULL){
            printf("Erreur d'allocation mémoire");
            exit(1);
        }
         // Initialisation de Q à 0 partout
        for(int i = 0; i < state_size; i++){
            for(int j = 0; j < action_size; j++){
                Q[i][j] = 0;
            } 
        }

    srand(time(NULL));
    
    for (int i = 0; i<= nbEpisodes;i++){

       
        switch(jeu) {

            // ################ Labyrinthe ################
            case 1: 

                // On choisit une position de départ au hasard

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
                    int a2;
                    if (rand() % 2 < 0.5) {
                        a2 = maxInd(Q1[s_next], action_size);
                        Q1[s][a] = Q1[s][a] + alpha * (stepOut.reward + gamma * Q2[s_next][a2] - Q1[s][a]);
                    }
                    else {
                        a2 = maxInd(Q2[s_next], action_size);
                        Q2[s][a] = Q2[s][a] + alpha * (stepOut.reward + gamma * Q1[s_next][a2] - Q2[s][a]);
                    }
                    
                    Q[s][a] = Q1[s][a] + Q2[s][a];
                    state_col = stepOut.new_col;
                    state_row = stepOut.new_row;
                    s_terminal = stepOut.done;
                }  
                break;

            // ################ Morpion ################
            case 2:
                printf("Le jeu du morpion n'est pas encore implémenté\n");
                return 1;
                break;

            case 3 : //trading

                //on choisit un état de départ au hasard
                ;
                int nb_titres = rand()%2; //0 ou 1 titre possédé
                int done = 0;
                int stock_price = rand()%10; //indique le prix du stock, divisé en 10 intervalles
                int prix_acquisition = rand() % 10; // entre 0 et 9 pour indiquer le prix du titre possédé
                int prix_acquisition_old = prix_acquisition;

                int i = 0;
                while (done == 0 && i < 50){
                    //i++;

                    int a = eps_greedy(action_size, epsilon, Q, prix_acquisition);
                    
                    //on ne peut acheter qu'un titre financier (version simple)
                    while ((nb_titres == 1 && a == 1) ||(nb_titres==0 && a == 0)){
                        a = eps_greedy(action_size, epsilon, Q, prix_acquisition);
                    }
                   
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
                    if ((double)rand() / (double)RAND_MAX < 0.5) {
                    Q1[indice][a] = Q1[indice][a] + alpha * (stepOut.reward + gamma * Q2[indice_next][maxInd(Q1[indice_next], action_size)] - Q1[indice][a]);
                    }
                    else {
                    Q2[indice][a] = Q2[indice][a] + alpha * (stepOut.reward + gamma * Q1[indice_next][maxInd(Q2[indice_next], action_size)] - Q2[indice][a]);
                    } 

                    Q[indice][a] = Q1[indice][a] + Q2[indice][a];

                    stock_price = stock_price + fluctu; 
                    prix_acquisition = s_next;
                    done = stepOut.done;
                    nb_titres = stepOut.nb_titres;
                    prix_acquisition_old = stepOut.prix_acquisition_old ;
                }

                break;

            default:
                printf("Jeu inconnu\n");
                exit(1);
        }

    }
    
    free_memory(state_size, (void**)Q);

    
    return 1;
}