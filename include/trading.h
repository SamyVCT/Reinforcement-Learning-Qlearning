
#include <stdio.h>
#include <stdlib.h>


enum action{
    sell,
    buy,
    none,
    number_actions

};

typedef enum action action ;

struct tradeOutput{
  int new_state;
  int reward;
  int done;
  int prix_achat;
  int nb_titres;

};

typedef struct tradeOutput tradeOutput;


