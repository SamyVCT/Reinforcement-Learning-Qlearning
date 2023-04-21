MAIN = src/main.c
FUNCTIONS = scr/functions.c
MAZEENV = src/mazeEnv.c
QLEARNING = src/algo1.c

INC=include/

CC=gcc 
CFLAGS=-Wall -Werror 

src/main : src/main.o src/functions.o src/mazeEnv.o src/algo1.o src/max.o
	$(CC) -I include/ -g -o src/main src/mazeEnv.o src/functions.o src/main.o src/algo1.o src/max.o $(CFLAGS)

src/main.o : src/main.c 
	$(CC) -I include/ -g -o src/main.o -c $(MAIN) $(CFLAGS)

src/algo1.o : src/algo1.c 
	$(CC) -I include/ -g -o src/algo1.o -c $(QLEARNING) $(CFLAGS)

src/max.o : src/max.c 
	$(CC) -I include/ -g -o src/max.o -c src/max.c $(CFLAGS)

src/dfs         : src/dfs.o src/functions.o src/mazeEnv.o
	gcc -I include/ -g -o src/dfs src/dfs.o src/functions.o src/mazeEnv.o -Wall

src/dfs.o       : src/dfs.c  include/mazeEnv.h
	gcc -I include/ -g -o src/dfs.o -c src/dfs.c -Wall

src/functions.o : src/functions.c include/functions.h
	gcc -I include/ -g -o src/functions.o -c src/functions.c -Wall

src/mazeEnv.o   : src/mazeEnv.c include/mazeEnv.h
	gcc -I include/ -g -o src/mazeEnv.o -c src/mazeEnv.c -Wall


clean:
	rm -f src/*.o
