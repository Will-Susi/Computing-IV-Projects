CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = FibLFSR.hpp
OBJ = FibLFSR.o 
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

.PHONY: all clean lint

all: PhotoMagic test lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

PhotoMagic: PhotoMagic.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o PhotoMagic test

lint:
	cpplint *.cpp *.hpp
