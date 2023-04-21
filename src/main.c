#include <main.h>



int main(int argc, char *argv[]){
    mazeEnv_make("../data/maze.txt");
    init_visited();

    int action_size = number_actions;
    int state_size = rows*cols;

    // Définition des paramètres de l'algorithme
    int nbEpisodes = 10000;
    double eps = 0.2; // strict positif
    double alpha = 0.9; //entre 0 et 1
    double gamma = 0.9; // facteur d'apprentissage entre 0 et 1

    printf("test 0\n");

    // On met les états sur les lignes et les actions possibles sur les colonnes
    float **Q = (float **)malloc(state_size * sizeof(float*));
    for(int i = 0; i < state_size; i++) Q[i] = (float *)malloc(action_size * sizeof(float));

    // Initialisation de Q à 0 partout
    for(int i = 0; i < state_size; i++){
        for(int j = 0; j < action_size; j++){
            Q[i][j] = 0.0;
        }
    }

    printf("test 1\n");

    // On vérifie que l'allocation mémoire a bien fonctionné et si on a le bon nombre d'arguments
    if (Q == NULL){
        printf("Erreur d'allocation mémoire");
        exit(1);
    }

    if(argc < 2){
        printf("Utilisation: %s <numéro algo>\n", argv[0]);
        exit(1);
    }

    // On lance l'algorithme choisi et compte le temps d'exécution

    clock_t start = clock();
    int algo = atoi(argv[1]);
    switch(algo){
        case 1:
            algo1(nbEpisodes, eps, alpha, gamma, Q, state_size, action_size);
            break;
        // case 2:
        //     algo2(nbEpisodes, eps, alpha, gamma, Q, state_size, action_size);
        //     break;
        // case 3:
        //     algo3(nbEpisodes, eps, alpha, gamma, Q, state_size, action_size);
        //     break;
        default:
            printf("Algorithme inconnu\n");
            exit(1);
    }
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

   printf("%d, %d \n", rows, cols);
   printf("number of actions :  %d \n", number_actions);

   // dfs(start_row,start_col);
   add_crumbs();
   mazeEnv_render();

    printf("test 2\n");
    // free memory

    for(int i = 0; i < state_size; i++) free(Q[i]);
    free(Q);


   return 0;
}