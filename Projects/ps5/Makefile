CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = EDistance.hpp
OBJ = EDistance.o 
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

.PHONY: all clean lint

all: EDistance lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

EDistance: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o EDistance

lint:
	cpplint *.cpp *.hpp
