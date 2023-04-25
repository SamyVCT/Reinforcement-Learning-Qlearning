# Indique au Makefile où trouver les fichiers .c et .o
vpath %.c src
vpath %.o src

CC=gcc 
CFLAGS=-Wall -Werror -I include/ -g

# Créé tous les .o puis le main (en 2 temps pour pouvoir trouver les dépendances)
all: functions.o mazeEnv.o algo1.o sarsa.o main.o
	make main

# Cherche tous les fichiers .o dans le dossier src
main: $(wildcard *.o)
	$(CC) -o $@ $^ $(CFLAGS)

src/main.o : main.c 
	$(CC) -o $@ -c $< $(CFLAGS)
	
src/algo1.o : algo1.c 
	$(CC) -o $@ -c $< $(CFLAGS)

src/sarsa.o : sarsa.c 
	$(CC) -o $@ -c $< $(CFLAGS)

# src/max.o : max.c 
# 	$(CC) -o $@ -c $< $(CFLAGS)

src/functions.o : functions.c
	$(CC) -o $@ -c $< $(CFLAGS)

src/mazeEnv.o   : mazeEnv.c 
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f src/*.o


