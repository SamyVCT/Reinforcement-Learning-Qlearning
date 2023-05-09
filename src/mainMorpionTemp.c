#include <morpion.h>


int main() {
    affichage = 1;

    init_plateau();

    jouer_coup(0, 0);
    jouer_coup(1, 1);
    jouer_coup(1, 0);
    jouer_coup(2, 2);
    jouer_coup(2, 0);
}