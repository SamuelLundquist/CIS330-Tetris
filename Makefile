.PHONY: run, build, clean

sources = $(wildcard *.cc)

run:
	./tetris

build: $(sources)
	g++ -o tetris $(sources) -lncurses -lpthread -g

clean:
	rm -f tetris

default: build
