#include <mazeEnv.h>
#include <functions.h>

char** mazeEnv;
int** visited;
int rows;
int cols;
int start_row;
int start_col;
int state_row;
int state_col;
int goal_row;
int goal_col;

// Initialise l'environnement du labyrinthe
void alloc_mazeEnv(){
     mazeEnv = malloc(rows * sizeof(char*));

     for(int i=0; i<rows; i++) {
         mazeEnv[i] = malloc(cols * sizeof(char*));
     }
}

// Créé le labyrinthe à partir d'un fichier texte dont le nom est passé en argument
void mazeEnv_make(char* file_name){
     char c;
     char rows_s[3] ={'\0'};
     char cols_s[3] ={'\0'};
     int rows_i = 0;
     int cols_i = 0;
     int swap = 0;

     FILE* file = fopen(file_name, "r");
     if (file == NULL){
        printf("Pointeur nul");
     }
     if (file) {
         /* lire la premiere ligne avant EOF */
         while( (c=getc(file)) != EOF) {
               if(c== '\n'){
                      break;
               } else if (c==',') {
                      swap = 1;
               } else if (!swap) {
                      rows_s[rows_i]=c;
                      rows_i++;
               } else {
                      cols_s[cols_i]= c;
                      cols_i++;
               }
         }
     }

     /* convertir le string en nombre */
     rows = atoi(rows_s);
     cols = atoi(cols_s);

     alloc_mazeEnv();

     for (int i=0; i<rows; i++){
         for (int j=0; j < cols; j++){
             c = getc(file);

             if (c=='\n'){
                 c = getc(file);
             } else if (c == 's'){
               start_row = i;
               start_col = j;
             } else if ( c == 'g'){
               goal_row = i;
               goal_col = j;
             }

             mazeEnv[i][j] = c;
         }
     }

     fclose(file);
}

// Affiche le labyrinthe
void mazeEnv_render(){
     for (int i=0; i<rows; i++) {
         for (int j=0; j< cols; j++){
             printf("%c ", mazeEnv[i][j]);
         }
         printf("\n");
     }
     printf("\n");
}

// Remet l'environnement à son état initial
void mazeEnv_reset(){
     state_row = start_row;
     state_col = start_col;
}

// Renvoie 1 si on est sur un mur, 0 sinon, prend en argument la position
int mazeEnv_is_wall(int row, int col){
     if (mazeEnv[row][col] == '+'){
         return 1;
     } else {
         return 0;
     }
}

//faire une action &observer récompense et où on se trouve
envOutput mazeEnv_step(action a){
    int reward = 0;
    int done = 0;
    envOutput stepOut;

    // enregistrer la position actuelle

    int old_row = state_row;
    int old_col = state_col;

    // si on est sur un bord de la grille
    if (a==up){
       state_row = max(0,state_row -1);
    }else if (a==down){
       state_row = min(rows-1,state_row +1);
    }else if (a==right){
       state_col = min(cols-1,state_col +1);
    }else if (a==left){
       state_col = max(0,state_col -1);
    }

    // si on est sur un mur
    if (mazeEnv[state_row][state_col] == '+'){
        reward = -100;

        // Remettre la position à l'ancienne position
        state_row = old_row;
        state_col = old_col;
    }
    
    if((state_row == goal_row) && (state_col == goal_col)){
       reward = 10000;
       done   = 1;
    }

    stepOut.reward = reward;
    stepOut.done   = done;
    stepOut.new_col = state_col;
    stepOut.new_row = state_row; 

   return stepOut;
}


