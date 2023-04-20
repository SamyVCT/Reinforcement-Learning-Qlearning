

float max(float* Q, int nbActions) {
    float max = Q[0];
    for (int i = 1; i < nbActions; i++) {
        if (Q[i] > max) {
            max = Q[i];
        }
    }
    return max;
}