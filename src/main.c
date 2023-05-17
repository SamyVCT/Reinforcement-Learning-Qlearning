#include <main.h>



int main(int argc, char *argv[]){

    // Verification des arguments.
    if(argc < 7){
        printf("Utilisation: %s <numéro algo> <nombre d'épisodes> <epsilon> <alpha> <gamma> <jeu>\n", argv[0]);
        exit(1);
    }
    #ifdef DEBUG
        printf("################ MODE DEBUG ################\n");
    #endif

    // Définition des paramètres de l'algorithme
    int nbEpisodes = atoi(argv[2]); 
    double eps = atof(argv[3]); // strict positif et inférieur à 1
    double alpha = atof(argv[4]); //entre 0 et 1
    double gamma = atof(argv[5]); // facteur d'apprentissage entre 0 et 1
    int algo = atoi(argv[1]);   // numéro de l'algorithme choisi
    int jeu = atoi(argv[6]);    // jeu choisi (maze, morpion, trading)

    #ifdef DEBUG
    clock_t start;
    start = clock();
    #endif

    // Définition des paramètres du jeu    
    int action_size;
    int state_size;

    // Définit le nombre d'actions et d'états possibles en fonction du jeu choisi et initialise les environnements.
    switch(jeu) {
        case 1: // Maze
            mazeEnv_make("data/maze.txt");
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
            state_size = 100; // 10 ranges of the price of the stock * 10 ranges of price for the share
            break;
        default:
            printf("Jeu inconnu\n");
            exit(1);
    }

    // Allocation de la matrice Q.
    // On met les états sur les lignes et les actions possibles sur les colonnes
    float **Q = (float **)malloc(state_size * sizeof(float*));
    for(int i = 0; i < state_size; i++) Q[i] = (float *)malloc(action_size * sizeof(float));

    // Initialisation de Q à 0 partout
    for(int i = 0; i < state_size; i++){
        for(int j = 0; j < action_size; j++){
            Q[i][j] = 0.0;
        } 
    }

    // On vérifie que l'allocation mémoire a bien fonctionné
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
            if(jeu == 1) {
                if(!sarsa(nbEpisodes, eps, alpha, gamma, Q, state_size, action_size)) {
                printf("Erreur dans l'algorithme 2\n");
                exit(1);
                }
            } else {
                printf("L'algorithme 2 n'est pas implémenté pour ce jeu\n");
            }           
            break;
        // case 3:
        //     algo3(nbEpisodes, eps, alpha, gamma, Q, state_size, action_size);
        //     break;
        default:
            printf("Algorithme inconnu\n");
            exit(1);
    }

    #ifdef DEBUG
        clock_t end = clock();
        

        // affichage de la matrice Q

        for(int i = 0; i < state_size; i++){
            printf("Etat %d : ", i);
            for(int j = 0; j < action_size; j++){
                printf("%f ", Q[i][j]);
            }
            printf("\n");
        }

        // On affiche le temps d'exécution
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Temps écoulé pour l'entrainement : %f\n", time_spent);
    #endif

    // On lance le jeu
    switch(jeu) {
        case 1:
            // calcul et affichage du parcours.
            action* path = malloc(500*sizeof(int));
            int path_size;
            resolveMaze(Q, action_size, path, &path_size);
            showResult(path, path_size);
            free(path);
            break;
        case 2:
            play_Morpion(Q, state_size,action_size);
            free_memory(state_size, (void**)S);
            break;
    
        case 3:
            render_trading(Q);
            break;
    }    

    free_memory(state_size, (void**)Q);

    return 0;
}