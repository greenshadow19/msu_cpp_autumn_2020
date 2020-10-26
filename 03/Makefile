CC = g++
FLAGS = -std=c++17 -Wall -fsanitize=address

all: test_pre 

test: test_pre
	./test_pre

test_pre: matrix.o test.o
	$(CC) $(FLAGS) -o test_pre matrix.o test.o

alloc.o: matrix.cpp
	$(CC) $(FLAGS) -c matrix.cpp -o matrix.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o test_pre
