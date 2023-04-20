MAIN = src/main.c
FUNCTIONS = scr/functions.c
MAZEENV = src/mazeEnv.c
QLEARNING = src/algo1.c

INC=include/

CC=gcc 
CFLAGS=-Wall -Werror 

src/main : src/main.o src/functions.o src/mazeEnv.o src/algo1.o
	$(CC) -o src/main src/main.o src/functions.o src/mazeEnv.o src/algo1.o $(CFLAGS)

src/main.o : src/main.c include/mazeEnv.h include/main.h include/algo1.h
	$(CC) -I include/ -o src/main.o -c $(MAIN) $(CFLAGS)

src/algo1.o : src/algo1.c include/mazeEnv.h include/algo1.h include/max.h src/max.c src/max.o
	$(CC) -I include/ -o src/algo1.o src/max.o -c $(QLEARNING) $(CFLAGS)

src/max.o : src/max.c include/max.h
	$(CC) -I include/ -o src/max.o -c src/max.c $(CFLAGS)

src/dfs         : src/dfs.o src/functions.o src/mazeEnv.o
	gcc -I include/ -g -o src/dfs src/dfs.o src/functions.o src/mazeEnv.o -Wall

src/dfs.o       : src/dfs.c  include/mazeEnv.h
	gcc -I include/ -g -o src/dfs.o -c src/dfs.c -Wall

src/functions.o : src/functions.c include/functions.h
	gcc -I include/ -g -o src/functions.o -c src/functions.c -Wall

src/mazeEnv.o   : src/mazeEnv.c include/mazeEnv.h
	gcc -I include/ -g -o src/mazeEnv.o -c src/mazeEnv.c -Wall

