#include <trading.h>

int prix_achat;
int prix_achat_old;
int nb_titres;


tradeOutput trading_step(action a){
    int reward = 0;
    int done = 0;
    tradeOutput stepOut;
    

    if (a == buy){
        nb_titres = 1;
        prix_achat_old = prix_achat;
        prix_achat = stock_price;
    }

    //si on vend ou achète au meilleur prix c'est gagné
    if ((a==sell && stock_price==9) || (a==buy && stock_price==0)){
        state_pos = stock_price;
        reward = 200;
        done = 1;
    }
    //on ne vend pas à perte
    else if(a==sell && prix_achat > stock_price){
        reward = -50;
        nb_titres = 0;
        state_pos = 10;
    }
    //on incite à toujours acheter des titres moins chers
    else if(a==buy && prix_achat_old > prix_achat){
        reward = 50;
        state_pos = stock_price;
    }

    stepOut.reward = reward;
    stepOut.done   = done;
    stepOut.new_state = state_pos;
    stepOut.prix_achat = prix_achat;
    stepOut.nb_titres = nb_titres;

    return stepOut;
}