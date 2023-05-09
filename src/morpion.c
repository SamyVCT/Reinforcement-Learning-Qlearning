#include <morpion.h>

char plateau[3][3];
int joueur_courant;
int affichage;
int nb_coups = 0;

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
        if(a_gagne(joueur_courant)){
            if(affichage) {
                render_plateau();
                printf("Le joueur %d a gagné\n",joueur_courant+1);
            }
        }
        else {
            if(affichage) render_plateau();
            joueur_courant = (joueur_courant + 1) % 2; // change de joueur
        }
        return 0;
    }
    else{
        printf("Case déjà occupée\n");
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

int search_state(float** Q, int state_size, int state[9]) {
    for (int i=0; i<state_size; i++) {
        for(int j=0; j<9; j++) {
            if (Q[i][j] != state[j]) {
                break;
            }
            if (j == 8) {
                return i;
            }
        }
    }
    return -1;
}
