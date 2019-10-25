CC=clang
CFLAGS=-O -Wall -g

all: bomb

bomb: bomb.c bomb.h
	$(CC) $(CFLAGS) -o bomb bomb.c -lncurses

clean:
	rm -f bomb

distclean: clean
