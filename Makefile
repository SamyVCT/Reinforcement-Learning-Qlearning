# Indique au Makefile où trouver les fichiers .c et .o
vpath %.c src
vpath %.o src

CC=gcc 
CFLAGS=-Wall -Werror -I include/ -g

all: main

main: functions.o mazeEnv.o qlearning.o sarsa.o main.o resolveMaze.o morpion.o trading.o
	$(CC) -o $@ $^ $(CFLAGS)

src/main.o : main.c 
	$(CC) -o $@ -c $< $(CFLAGS)
	
src/qlearning.o : qlearning.c 
	$(CC) -o $@ -c $< $(CFLAGS)

src/sarsa.o : sarsa.c 
	$(CC) -o $@ -c $< $(CFLAGS)

src/resolveMaze.o : resolveMaze.c 
	$(CC) -o $@ -c $< $(CFLAGS)

src/functions.o : functions.c
	$(CC) -o $@ -c $< $(CFLAGS)

src/mazeEnv.o   : mazeEnv.c 
	$(CC) -o $@ -c $< $(CFLAGS)

src/morpion.o : morpion.c
	$(CC) -o $@ -c $< $(CFLAGS)

src/trading.o : trading.c
	$(CC) -o $@ -c $< $(CFLAGS)

src/mainMorpionTemp.o : mainMorpionTemp.c
	$(CC) -o $@ -c $< $(CFLAGS)

morpion: mainMorpionTemp.o morpion.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o
	rm -f main


