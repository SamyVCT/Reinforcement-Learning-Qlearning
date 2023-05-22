#ifndef MORPION_H
#define MORPION_H

#include <stdlib.h>
#include <stdio.h>
#include <functions.h>
#include <math.h>

extern char plateau[3][3];
extern int joueur_courant;
extern int affichage;
extern int nb_coups;

enum player {PLAYER1, PLAYER2};

// Initialise le plateau de morpion dans la variable "plateau"
// Renvoie 0
int init_plateau();

// INPUT : action a à jouer
// Joue un coup sur le plateau de morpion en position "a" et change de joueur. 
// OUTPUT : 0 si le coup est joué, 1 si la case est déjà occupée, 2 si le plateau est plein
int jouer_coup(int a);

// INPUT : joueur = PLAYER1 ou PLAYER2
// OUTPUT 1 si "joueur" a gagné, 0 sinon
int a_gagne(int joueur);

// Affiche le plateau de morpion
// OUTPUT : 0
int render_plateau();

// Transforme le plateau de morpion en un indice d'état pour Q
// OUTPUT : indice de l'état en cours
int board_to_state();

// INPUT : matrice des états et actions après entraiement, nombre d'états, nombre d'actions.
// Permet au joueur de jouer contre l'ordinateur
// OUTPUT : 0
int play_Morpion(float** Q, int state_size, int action_size);

#endif