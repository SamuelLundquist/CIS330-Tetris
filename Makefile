.PHONY: run, build, clean

start:
	./game

build: game.c
	gcc -o game game.c -lncurses

clean:
	rm -f *.o game

default: build
