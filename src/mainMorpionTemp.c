#include <morpion.h>


int main() {
    affichage = 1;

    init_plateau();

    jouer_coup(0, 0);
    jouer_coup(1, 1);
    jouer_coup(1, 0);
    jouer_coup(2, 2);
    jouer_coup(2, 0);

    int test[2];
    test[0] = 1;
    test[1] = 1;

    int test2[2];
    test2[0] = 1;
    test2[1] = 1;

    printf("%d\n", test == test2);
}