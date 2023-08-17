CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
DEPS = main.hpp
OBJ = main.o 
LIB = -lboost_unit_test_framework -lboost_date_time

.PHONY: all clean lint

all: ps7 lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

ps7: main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o ps7

lint:
	cpplint *.cpp *.hpp
