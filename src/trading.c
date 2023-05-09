#include <trading.h>

int rows;
int cols;
int start_pos;

envOutput trading_step(action a){
    int reward = 0;
    int done = 0;
    envOutput stepOut;
    
    // enregistrer la position actuelle

    int old_pos = state_pos;

    if (a==buy){

    }else if(a==sell){

    }else if(a==none){

    }

    stepOut.reward = reward;
    stepOut.done   = done;
    stepOut.new_pos = state_pos;

    return stepOut;
}