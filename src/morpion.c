#include <morpion.h>

char plateau[3][3];
int joueur_courant;
int affichage = 0;
int nb_coups = 0;

int init_plateau(){ 
    int i,j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            plateau[i][j]='.';
        }
    }

    joueur_courant=PLAYER1;
    nb_coups = 0;
    return 0;
}


int jouer_coup(int a){ 
    if(nb_coups == 9) {
        printf("Match nul\n");
        return 2;
    }
    int x = a / 3;
    int y = a % 3;

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
        nb_coups++;
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

int board_to_state() {
    int etat = 0;
    int state[9];
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

    // Conversion en base 10 du plateau écrit en base 3.
    for (int i=0; i<9; i++) {
        etat += (state[i] * pow(3, 8-i));
    }
    return etat;
}


int play_Morpion(float** Q, int state_size, int action_size) {
    init_plateau();
    int k = 0;
    affichage = 1;
    int fin = 0;


    // arrête la partie si un joueur gagne ou si le plateau est plein.
    while(!fin && nb_coups < 9) {

        // On récupère le state actuel
        int state_index;
        state_index = board_to_state();


        // On récupère l'action à jouer et on la joue
        int a;
        a = maxInd(Q[state_index], action_size);
        #ifdef DEBUG
        printf("Valeurs de Q : %f %f %f %f %f %f %f %f %f\n", Q[state_index][0], Q[state_index][1], Q[state_index][2], Q[state_index][3], Q[state_index][4], Q[state_index][5], Q[state_index][6], Q[state_index][7], Q[state_index][8]);
        #endif
        jouer_coup(a);


        if(a_gagne(PLAYER1)) {
            printf("Le joueur %d a gagné\n", PLAYER1);
            fin = 1;
            break;
        }


        // On récupère le coup du joueur et on le joue
        int coup_joueur;
        printf("Entrez votre coup (1 à 9) : ");
        scanf("%d", &coup_joueur);
        coup_joueur--;
        jouer_coup(coup_joueur);

        if(a_gagne(PLAYER2)) {
            printf("Le joueur %d a gagné\n", PLAYER2);
            fin = 1;
        }

        k++;
    }
    return 0;
}
