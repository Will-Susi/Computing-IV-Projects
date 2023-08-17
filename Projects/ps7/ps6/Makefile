CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = RandWriter.hpp
OBJ = RandWriter.o 
LIB = -lboost_unit_test_framework

.PHONY: all clean lint

all: TextWriter test lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

TextWriter: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o TextWriter test

lint:
	cpplint *.cpp *.hpp
