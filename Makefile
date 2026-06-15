makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm

OBJS = main.o funcs.o

routes: $(OBJS)
	$(CC) $(OBJS) -o routes $(LDFLAGS)

main.o: main.c funcs.h
	$(CC) $(CFLAGS) -c main.c

funcs.o: funcs.c funcs.h
	$(CC) $(CFLAGS) -c funcs.c

clean:
	rm -f *.o routes
