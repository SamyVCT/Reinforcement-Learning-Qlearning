#include <stdlib.h>
#include <stdio.h>

extern char plateau[3][3];
extern int joueur_courant;
extern int affichage;

enum player {PLAYER1, PLAYER2};

int init_plateau();

int jouer_coup(int x, int y);

int a_gagne(int joueur);

int render_plateau();

int board_to_state(int state[9]);

int search_state(float** Q, int state_size, int state[9]);