CC = gcc
CFLAGS = -Wall -Wextra

./arena.o: ./arena.c ./arena.h
	$(CC) $(CFLAGS) -c ./arena.c -o ./arena.o

clean:
	rm ./arena.o
