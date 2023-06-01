#include <main.h>



int main(int argc, char *argv[]){

    // Verification des arguments.
    if(argc < 7){
        printf("Utilisation: %s <numero algo> <nombre d'episodes> <epsilon> <alpha> <gamma> <jeu>\n", argv[0]);
        exit(1);
    }
    #ifdef DEBUG
        printf("\x1b[31m################ MODE DEBUG ################ \x1b[m\n");
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

    // Allocation de la matrice Q2 pour Double Q-learning.
    // On met les états sur les lignes et les actions possibles sur les colonnes
    float **Q2 = (float **)malloc(state_size * sizeof(float*));
    for(int i = 0; i < state_size; i++) Q2[i] = (float *)malloc(action_size * sizeof(float));

    // Initialisation de Q2 à 0 partout
    for(int i = 0; i < state_size; i++){
        for(int j = 0; j < action_size; j++){
            Q2[i][j] = 0.0;
        } 
    }

    // On vérifie que l'allocation mémoire a bien fonctionné
    if (Q == NULL || Q2 == NULL){
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
        case 3:
            if(!doubleqlearning(jeu,nbEpisodes, eps, alpha, gamma, Q, Q2, state_size, action_size)) {
                printf("Erreur dans l'algorithme 3\n");
                exit(1);
            }

            break;
        default:
            printf("Algorithme inconnu : %d\n",algo);
            exit(1);
    }

    #ifdef DEBUG
        clock_t end = clock();
        

        // affichage de la matrice Q
        //print_Q(Q, state_size, action_size);
        

        // On affiche le temps d'exécution
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTemps écoulé pour l'entrainement : \x1b[31m%fs\x1b[m\n\n", time_spent);
    #endif

    // On lance le jeu
    switch(jeu) {
        case 1:
            ;
            // calcul et affichage du parcours.
            action* path = malloc(500*sizeof(int));
            int path_size;
            resolveMaze(Q, action_size, path, &path_size);
            showResult(path, path_size);
            free(path);
            break;
        case 2:
            ;
            char c = 'y';
            while(c == 'y') {
                play_Morpion(Q, state_size,action_size);
                printf("Voulez-vous rejouer ? (y/n)\n");
                scanf("%s", &c);
            }
            break;
    
        case 3:
        ;
            int n = 0;
            int argent = 0;
            printf("Combien d'entrainements?\n");
            scanf("%d", &n);
            for (int k = 0; k<n; k++){            
                argent = argent + render_trading(Q);
                //printf("k = %d\n",k);

                for(int i = 0; i < state_size; i++){
                    for(int j = 0; j < action_size; j++){
                        Q[i][j] = 0;
                        Q2[i][j] = 0;
                    } 
                }

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
                    case 3:
                        if(!doubleqlearning(jeu,nbEpisodes, eps, alpha, gamma, Q, Q2, state_size, action_size)) {
                            printf("Erreur dans l'algorithme 3\n");
                            exit(1);
                        }

                        break;
                    default:
                        printf("Algorithme inconnu : %d\n",algo);
                        exit(1);
                } 
                
                //print_Q(Q, state_size, action_size);

            }

            printf("Argent gagne au final sur %d entrainements avec l'algo %d : %d\nMoyenne par entrainement : %d \n",n,algo,argent, argent/n);

        break;
    }    

    free_memory(state_size, (void**)Q);
    free_memory(state_size, (void**)Q2);


    return 0;
}