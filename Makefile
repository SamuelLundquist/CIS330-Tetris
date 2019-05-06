.PHONY: run, build, clean

start:
	./game

build: game.c
	g++ -o game game.cpp -lncurses

clean:
	rm -f *.o game

default: build
