.PHONY: run, build, clean

run:
	./game

build: Tetris-windows.cpp
	g++ -o game Tetris-windows.cpp -lncurses

clean:
	rm -f game

default: build
