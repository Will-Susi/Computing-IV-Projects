CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = PTree.hpp
OBJ = PTree.o
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

.PHONY: all clean lint

all: PTree lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

PTree: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o PTree

lint:
	cpplint *.cpp *.hpp
