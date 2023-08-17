CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

.PHONY: all clean lint

all: sfml-app lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

sfml-app: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o sfml-app

lint:
	cpplint *.cpp *.hpp
