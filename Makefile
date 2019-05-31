.PHONY: run, build, clean

sources = $(wildcard *.cc)

run:
	./test

build: $(sources)
	g++ -o test $(sources) -lncurses -lpthread

clean:
	rm -f test

default: build
