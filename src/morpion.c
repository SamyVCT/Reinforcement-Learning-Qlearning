#include <morpion.h>

char plateau[3][3];
int joueur_courant;
int affichage = 0;
int nb_coups = 0;
int** S;

int init_states(int state_size) { // Créé une table de tous les plateaux de morpion possibles (state_size = 3^9)
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

int init_plateau(){ // Initialise le plateau de morpion
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


// Joue un coup sur le plateau de morpion en position "a" et change de joueur. 
// Renvoie 0 si le coup est joué, 1 si la case est déjà occupée, 2 si le plateau est plein
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

int a_gagne(int joueur){ // Renvoie 1 si "joueur" a gagné, 0 sinon
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

int render_plateau(){ // Affiche le plateau de morpion
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

int board_to_state(int state[9]) { // Transforme le plateau actuel en un état enregistré dans un tableau de int en base 3
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


// Recherche l'état "state" dans le tableau S et renvoie
//  son indice qui correspond à l'état actuel pour être utilisé dans Q. Return -1 si l'état n'est pas trouvé.
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


// Prend en argument la matrice des états et actions après entraiement et permet au joueur de jouer
//  contre l'ordinateur.
int play_Morpion(float** Q, int state_size, int action_size) {
    init_plateau();
    int x, y, k = 0;
    affichage = 1;
    int fin = 0;


    // arrête la partie si un joueur gagne ou si le plateau est plein.
    while(!fin && nb_coups < 9) {

        // On récupère le state actuel
        int state[9];
        board_to_state(state);

        int state_index;
        state_index = search_state(state_size, state);


        // On récupère l'action à jouer et on la joue
        int a;
        a = maxInd(Q[state_index], action_size);

        jouer_coup(a);


        if(a_gagne(PLAYER1)) {
            printf("Le joueur %d a gagné\n", PLAYER1);
            fin = 1;
            break;
        }


        // On récupère le coup du joueur et on le joue
        int coup_joueur;
        printf("Entrez votre coup (1 à 9) : ");
        scanf("%d ", &coup_joueur);
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
