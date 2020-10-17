CC = g++
FLAGS = -std=c++17 -Wall

all: test_pre 

test: test_pre
	./test_pre

test_pre: parser.o test.o
	$(CC) $(FLAGS) -o test_pre parser.o test.o

alloc.o: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp -o parser.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o test_pre
