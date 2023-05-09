#include <morpion.h>

char plateau[3][3];
int joueur_courant;
int affichage = 0;
int nb_coups = 0;
int** S;

int init_states(int state_size) {
    S = malloc(state_size * sizeof(int*));

    // S est un tableau de tous les plateaux possibles sous forme de tableau de int de taille 9
    for (int i = 0; i < state_size; i++) {
        S[i] = malloc(9 * sizeof(int));

        // S[i] = i en base 3 sous forme d'un tableau de int
        int j = 0;
        int k;
        k = i;
        while (k > 0) {
            S[i][8-j] = k % 3;
            k = k / 3;
            j++;
        }
        while (j < 9) {
            S[i][8-j] = 0;
            j++;
        }
    }
    return 0;
}


int init_plateau(){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            plateau[i][j]='.';
        }
    }

    joueur_courant=PLAYER1;
    return 0;
}

int jouer_coup(int x, int y){
    if(nb_coups == 9) {
        printf("Match nul\n");
        return 2;
    }

    if(plateau[x][y]=='.'){
        switch(joueur_courant){
            case PLAYER1:
                plateau[x][y]='X';
                break;
            case PLAYER2:
                plateau[x][y]='O';
                break;
            default:
                printf("Erreur joueur\n");
                return 1;
        }
        if(affichage) render_plateau();
        joueur_courant = (joueur_courant + 1) % 2; // change de joueur
        return 0;
    }
    else{

        //printf("Case déjà occupée\n");
        return 1;
    }
}

int a_gagne(int joueur){
    int i;
    char symbole;
    switch(joueur){
        case PLAYER1:
            symbole='X';
            break;
        case PLAYER2:
            symbole='O';
            break;
        default:
            printf("Erreur joueur\n");
            return 0;
    }

    // Test des combinaisons gagnantes
    for(i=0;i<3;i++){
        if(plateau[i][0]==symbole && plateau[i][1]==symbole && plateau[i][2]==symbole){
            return 1;
        }
        if(plateau[0][i]==symbole && plateau[1][i]==symbole && plateau[2][i]==symbole){
            return 1;
        }
    }
    if(plateau[0][0]==symbole && plateau[1][1]==symbole && plateau[2][2]==symbole){
        return 1;
    }
    if(plateau[0][2]==symbole && plateau[1][1]==symbole && plateau[2][0]==symbole){
        return 1;
    }
    return 0;
}

int render_plateau(){
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            printf("%c ",plateau[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int board_to_state(int state[9]) {
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            switch (plateau[i][j]) {
                case 'X':
                    state[i*3+j] = 1;
                    break;
                case 'O':
                    state[i*3+j] = 2;
                    break;
                default:
                    state[i*3+j] = 0;
                    break;
            }
        }
    }
    return 1;
}

int search_state(int state_size, int state[9]) {
    for (int i=0; i<state_size; i++) {
        for(int j=0; j< 9; j++) {
            if (S[i][j] != state[j]) {
                break;
            }
            if (j == 8) {
                return i;
            }
        }
    }
    return -1;
}

int play_Morpion(float** Q, int state_size, int action_size) {
    init_plateau();
    int x, y, k = 0;
    affichage = 1;
    int fin = 0;
    while(!fin && k < 5) {
        int state[9];
        board_to_state(state);

        int state_index;
        state_index = search_state(state_size, state);

        int a;
        a = maxInd(Q[state_index], action_size);
        x = a / 3;
        y = a % 3;

        jouer_coup(x, y);

        if(a_gagne(PLAYER1)) {
            printf("Le joueur %d a gagné\n", joueur_courant+1);
            fin = 1;
            break;
        }

        int coup_joueur_x, coup_joueur_y;
        printf("Entrez votre coup (x et y) : ");
        scanf("%d %d", &coup_joueur_x, &coup_joueur_y);
        jouer_coup(coup_joueur_x, coup_joueur_y);
        k++;
        if(a_gagne(PLAYER2)) {
            printf("Le joueur %d a gagné\n", joueur_courant+1);
            fin = 1;
        }

        k++;
    }
    


    return 0;
}
