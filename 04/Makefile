CC = g++
FLAGS = -std=c++17 -Wall -fsanitize=address

all: test_pre 

test: test_pre
	./test_pre

test_pre: BigInt.o test.o
	$(CC) $(FLAGS) -o test_pre BigInt.o test.o

alloc.o: BigInt.cpp
	$(CC) $(FLAGS) -c BigInt.cpp -o matrix.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o test_pre
