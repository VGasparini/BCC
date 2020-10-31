all: build run 

build: test_$(test).cpp graph.hpp
	g++ -O2 -lm -o test test_$(test).cpp

run:
	reset && ./test < $(input)
