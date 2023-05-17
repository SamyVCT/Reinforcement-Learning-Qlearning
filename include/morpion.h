#include <stdlib.h>
#include <stdio.h>
#include <functions.h>
#include <math.h>

extern char plateau[3][3];
extern int joueur_courant;
extern int affichage;
extern int nb_coups;
extern int** S;

enum player {PLAYER1, PLAYER2};

int init_plateau();

int jouer_coup(int a);

int a_gagne(int joueur);

int render_plateau();

int board_to_state();

int search_state(int state_size, int state[9]);

int init_states(int state_size);

int play_Morpion(float** Q, int state_size, int action_size);
