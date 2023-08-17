CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = Sokoban.hpp
OBJ = Sokoban.o
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

.PHONY: all clean lint

all: Sokoban lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

Sokoban: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o Sokoban

lint:
	cpplint *.cpp *.hpp