CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = Checkers.hpp
OBJ = Checkers.o 
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

.PHONY: all clean lint

all: Checkers lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

Checkers: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o Checkers

lint:
	cpplint *.cpp *.hpp
