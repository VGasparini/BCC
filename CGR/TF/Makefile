FILE = src/main.cpp
OUT = ray
FLAGS = -lm -fopenmp -lsfml-system -lsfml-graphics -lsfml-window -lpthread -std=c++11 -Ofast
CC = g++

all: compile run

compile:
	$(CC) $(FILE) -o $(OUT) $(FLAGS)
run:
	./$(OUT) < scene

.PHONY: ALL
