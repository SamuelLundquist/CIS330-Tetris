.PHONY: run, build, clean

run:
	./test

build: game.cc
	g++ -o test game.cc -lncurses

clean:
	rm -f test

default: build
