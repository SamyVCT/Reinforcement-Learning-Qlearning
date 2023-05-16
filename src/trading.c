#include <trading.h>


tradeOutput trading_step(trade_action a, int prix_acquisition ,int prix_acquisition_old, int nb_titres, int stock_price){
    int reward = 0;
    int done = 0;
    tradeOutput stepOut;

    //0 = sell, 1 = buy, 2 = none
    if (a == 1){
        nb_titres = 1;
        prix_acquisition_old = prix_acquisition;
        prix_acquisition = stock_price;

            //on incite à toujours acheter des titres moins chers
        if(prix_acquisition_old > prix_acquisition){
            reward = 50;
        }
            //pas d'interet à acheter au plus haut prix
        if (prix_acquisition == 9){
            reward = -25;
        }
    }
    
    if(a==0){
        nb_titres = 0;
        prix_acquisition_old = prix_acquisition;
        prix_acquisition = stock_price;
           
        //on ne vend pas à perte
        if(prix_acquisition > stock_price){
            reward = -50;
        }

        //on incite à toujours vendre des titres plus chers
        if(prix_acquisition_old < prix_acquisition){
        reward = 50;
        }

    }

    //si on vend ou achète au meilleur prix c'est gagné
    if ((a==0 && stock_price==9 && prix_acquisition_old != 9) || (a==1 && stock_price==0)){
        prix_acquisition_old = prix_acquisition;
        prix_acquisition = stock_price;
        reward = 200;
        if(a==0) {
            nb_titres = 0;
        }
        else {
            nb_titres = 1;
        }
        done = 1;
    }


    
    stepOut.reward = reward;
    stepOut.done   = done;
    stepOut.prix_acquisition = prix_acquisition;
    stepOut.nb_titres = nb_titres;
    stepOut.prix_acquisition_old = prix_acquisition_old;

    return stepOut;
}
