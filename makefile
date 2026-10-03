CC = gcc
CFLAGS = -Wall -Wextra

./arena.o: ./arena.c
	$(CC) $(CFLAGS) -c ./arena.c ./arena.o

clean:
	rm ./arena.o
