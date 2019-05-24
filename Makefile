.PHONY: run, build, clean

sources = $(wildcard *.cc)

run:
	./test

build: $(sources)
	g++ -o test $(sources) -lncurses

clean:
	rm -f test

default: build
