void algo1(){
    int action_size = 4;
    int state_size = rows*cols; //voir toutes les cases vides (sans +);
   
   // Q = np.zeros((state_size, action_size))
    int **Q = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) Q[i] = (int *)malloc(cols * sizeof(int));
    
    //int *Q = (int *)malloc(state_size * action_size * sizeof(int));
   
    double alpha = 0.2;// taux d'apprentissage entre 0 et 1

    Q[state*action_size + action] = Q[state*action_size + action] + alpha * (reward + gamma * np.max(Q[new_state, :]) — Q[state*action_size + action])


}

action esp_greedy(int nbActions, float eps, int** Q, int state){
    int action;
    if (rand() < eps){
        action = rand() % nbActions; // Choisir une action au hasard
    }else{
        action = argmax(Q[state]); // Choisir l'action qui maximise Q
    }
    return action;
}