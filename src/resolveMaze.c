#include <resolveMaze.h>


// Prend en argument la matrice des états et actions après entraiement et permet de résoudre le labyrinthe,
// le nombre d'actions action_size et la taille du chemin "path_size" et le chemin "path" sont modifiés par la fonction.
int resolveMaze(float** Q, int action_size, action* path, int* path_size){
    mazeEnv_reset();
    int state = start_row*cols + start_col;
    int act = 0;
    int i = 0;
    while(state != goal_row*cols + goal_col && i < cols*rows){
        act = maxInd(Q[state], action_size);
        path[i] = act;
        switch(act){ // On part du principe que l'on ne peut pas sortir du labyrinthe si la matrice Q est correcte
                        // de même, on ne peut pas se retrouver sur un mur
            case up: 
                state = state - cols;
                break;
            case down:
                state = state + cols;
                break;
            case left:
                state = state - 1;
                break;
            case right:
                state = state + 1;
                break;
        }
        i++;
    }
    *path_size = i;
    return 1;
}

// Prend en argument le chemin "path" et sa taille "path_size" et affiche le labyrinthe avec le chemin trouvé.
int showResult(action* path, int path_size) {
    mazeEnv_reset();

    for (int i = 0; i < path_size-1; i++){
        mazeEnv_step(path[i]);
        mazeEnv[state_row][state_col] = 'o';
        
    }
    mazeEnv_render();
    return 1;
}

