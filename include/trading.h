#ifndef TRADING_H
#define TRADING_H
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

/* INPUT : a = action à réaliser, prix_acquisition = combien vaut le titre possédé, prix_acquisition_old = combien vaut le précédent titre possédé, nb_titres = combien on possède de titres, stock_price = combien coute le titre sur le marché
* OUTPUT : struct qui contient le reward accordé, done = si l'action est optimale, et les nouveaux prix d'acquisition et nombre de titres
 * DESCRIPTION : Fonction qui effectue une étape de trading avec une action donnée
 */
tradeOutput trading_step(trade_action a, int prix_acquisition, int prix_acquisition_old, int nb_titres, int stock_price);

/* INPUT : matrice des récompenses
 * OUTPUT : void
 * DESCRIPTION : Fonction qui affiche les étapes de trading par jour
 */
void render_trading(float** Q);

#endif