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

void render_trading(float** Q){
    //on part d'un état initial, puis on lit le fichier jour par jour et l'algo décide
    // de l'action à réaliser grâce aux valeurs de Q
    int jour = 0;

    //nb_titre et prix d'acquisition random au début
    int nb_titres = 1; //0 ou 1 titre possédé
    int prix_acquisition = rand() % 10; // entre 0 et 9 pour indiquer le prix du titre possédé
    

    //lecture des données
    FILE *fp;
    int real_stock_price;
  
    fp = fopen("data/trading_day.csv","r");
    //recup min max
    int mini = 5687;
    int maxi = 7570;
    int delta = (maxi - mini) /10;

    int argent_tot = -(mini + delta*prix_acquisition);
    printf("Jour 0 \n  Argent : %d\n", argent_tot);
    
    while(1) {
        fscanf(fp,"%d\n", &real_stock_price);
        jour++;

        if( feof(fp) ) { 
            break ;
        }

        //prix_matrice  = prix - mini / delta -> dans [0,9]
        int indice_stock_price = (real_stock_price - mini) / delta;
        
        trade_action a ;
        int change = 0;

        int indice_ligne_Q = 10*indice_stock_price + prix_acquisition;

        if (nb_titres == 0){
            if (Q[indice_ligne_Q][1] > Q[indice_ligne_Q][2]) {a = 1; change = 1;}
            else a = 2;
        }
        if (nb_titres == 1){
            if (Q[indice_ligne_Q][0] > Q[indice_ligne_Q][2]) {a = 0; change = 1 ;}
            else a = 2;
        }

        if (a==0 && change==1){
            char* action = "vendre";
            nb_titres = 0;
            prix_acquisition = indice_stock_price;
            argent_tot = argent_tot + (mini+delta*prix_acquisition);
            printf("Jour %d \n Prix du stock (indice) : %d, Prix du stock (réel) : %d, Action : %s, Argent : %d\n", jour, indice_stock_price, real_stock_price, action, argent_tot);

        }
        else if (a==1 && change==1){
            char* action = "acheter";
            nb_titres = 1;
            prix_acquisition = indice_stock_price;
            argent_tot = argent_tot - (mini+delta*prix_acquisition);
            printf("Jour %d \n Prix du stock (indice) : %d, Prix du stock (réel) : %d, Action : %s, Argent : %d\n", jour, indice_stock_price, real_stock_price,action, argent_tot);

        }

    }
    fclose(fp);


}