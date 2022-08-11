CC=gcc
CFLAGS= -c -Wall 
FILENAME=calc

all: out

out: stack.o main.o calc.o
	$(CC) stack.o main.o calc.o -o $(FILENAME)

stack.o: stack.c
	$(CC) $(CFLAGS) stack.c

calc.o: calc.c
	$(CC) $(CFLAGS) calc.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clear:
	rm *.o
