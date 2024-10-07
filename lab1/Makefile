all: run

build:
	g++ -o some.exe some.cpp

main:
	g++ -o Lab1.exe main.cpp

run:
	make build
	./some.exe
	make main
	./Lab1.exe

.PHONY: all run