
#include <stdio.h>
#include <stdlib.h>


enum action{
    sell,
    buy,
    none,
    number_actions

};

typedef enum action action ;

struct envOutput{
  int new_pos;
  int reward;
  int done;

};

typedef struct envOutput envOutput;


