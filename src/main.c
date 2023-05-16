#include <main.h>



int main(int argc, char *argv[]){

    // Verification des arguments.
    if(argc < 7){
        printf("Utilisation: %s <numéro algo> <nombre d'épisodes> <epsilon> <alpha> <gamma> <jeu>\n", argv[0]);
        exit(1);
    }

    if(argc > 7) {
        printf("################ MODE DEBUG ################\n");
        debug = 1;
    } else debug = 0;


    // Définition des paramètres de l'algorithme
    int nbEpisodes = atoi(argv[2]); 
    double eps = atof(argv[3]); // strict positif et inférieur à 1
    double alpha = atof(argv[4]); //entre 0 et 1
    double gamma = atof(argv[5]); // facteur d'apprentissage entre 0 et 1
    int algo = atoi(argv[1]);   // numéro de l'algorithme choisi
    int jeu = atoi(argv[6]);    // jeu choisi (maze, morpion, trading)

    clock_t start;
    if(debug) {
        // On compte le temps d'exécution
        start = clock();
    }

    // Définition des paramètres du jeu    
    int action_size;
    int state_size;

    switch(jeu) {
        case 1: // Maze
            mazeEnv_make("data/maze.txt");
            init_visited();
            action_size = number_actions;
            state_size = rows*cols;
            break;
        case 2: // Morpion
            action_size = 9;
            state_size = 19683; // 3^9 états possibles
            init_states(state_size);
            break;
        case 3: // Trading
            action_size = 3; // buy, sell, none
            state_size = 10; // 10 ranges of the price of the stock
            break;
        default:
            printf("Jeu inconnu\n");
            exit(1);
    }

    // On met les états sur les lignes et les actions possibles sur les colonnes
    float **Q = (float **)malloc(state_size * sizeof(float*));
    for(int i = 0; i < state_size; i++) Q[i] = (float *)malloc(action_size * sizeof(float));

    // Initialisation de Q à 0 partout
    for(int i = 0; i < state_size; i++){
        for(int j = 0; j < action_size; j++){
            Q[i][j] = 0.0;
        } 
    }

    // On vérifie que l'allocation mémoire a bien fonctionné et si on a le bon nombre d'arguments
    if (Q == NULL){
        printf("Erreur d'allocation mémoire");
        exit(1);
    }


    // On lance l'algorithme choisi

    switch(algo){
        case 1:
            if(!qlearning(jeu,nbEpisodes, eps, alpha, gamma, Q, state_size, action_size)) {
                printf("Erreur dans l'algorithme 1\n");
                exit(1);
            }
            break;
        case 2:
                if(!sarsa(nbEpisodes, eps, alpha, gamma, Q, state_size, action_size)) {
                printf("Erreur dans l'algorithme 2\n");
                exit(1);
            }             
            break;
        // case 3:
        //     algo3(nbEpisodes, eps, alpha, gamma, Q, state_size, action_size);
        //     break;
        default:
            printf("Algorithme inconnu\n");
            exit(1);
    }

    if (debug) {
        clock_t end = clock();
        
        // On affiche le temps d'exécution
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Temps écoulé pour l'entrainement : %f\n", time_spent);

        // affichage de la matrice Q

        for(int i = 0; i < state_size; i++){
            printf("Etat %d : ", i);
            for(int j = 0; j < action_size; j++){
                printf("%f ", Q[i][j]);
            }
            printf("\n");
        }
    }

    if(jeu == 1) {
        // calcul et affichage du parcours.

        action* path = malloc(500*sizeof(int));
        int path_size;
        resolveMaze(Q, action_size, path, &path_size);
        showResult(path, path_size);
        free(path);
    }

    if(jeu == 2) {
       play_Morpion(Q, state_size,action_size);
       free_memory(state_size);
    }
    
    if(jeu == 3) {
        //trading(Q,state_size, action_size);
        //render_trading();
    }

    // free memory
    for(int i = 0; i < state_size; i++) free(Q[i]);
    free(Q);

   return 0;
}