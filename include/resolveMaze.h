#include <mazeEnv.h>
#include <stdio.h>
#include <functions.h>

int resolveMaze(float** Q, int action_size, action* path, int* path_size);

int showResult(action* path, int path_size);