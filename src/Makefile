CC=gcc
CFLAGS= -c -Wall 
FILENAME=calc

all: out

out: stack.o main.o 
	$(CC) stack.o main.o -o $(FILENAME)

stack.o: stack.c
	$(CC) $(CFLAGS) stack.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

