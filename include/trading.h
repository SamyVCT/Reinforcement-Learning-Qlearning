
#include <stdio.h>
#include <stdlib.h>
#include <functions.h>

enum trade_action{
    sell,
    buy,
    none,
};

typedef enum trade_action trade_action ;

struct tradeOutput{
  int reward;
  int done;
  int prix_acquisition;
  int prix_acquisition_old;
  int nb_titres;

};

typedef struct tradeOutput tradeOutput;


tradeOutput trading_step(trade_action a, int prix_acquisition, int prix_acquisition_old, int nb_titres, int stock_price);

void render_trading(float** Q);
