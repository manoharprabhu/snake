CC=g++
LIBS=-lsfml-graphics -lsfml-system -lsfml-window
FLAGS=-g -std=c++11 -Wall -pedantic

all: directory clean copy
	$(CC) $(FLAGS) -o Build/snake src/main.cpp src/snake.cpp $(LIBS)

directory:
	mkdir -p Build

clean:
	rm -f Build/snake
	
copy:
	cp arial.ttf Build/arial.ttf

.PHONY: directory clean copy
