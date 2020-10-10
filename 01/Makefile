CC = g++
FLAGS = -std=c++17 -Wall

all: test_pre 

test: test_pre
	./test_pre

test_pre: alloc.o test.o
	$(CC) $(FLAGS) -o test_pre alloc.o test.o

alloc.o: allocator.cpp
	$(CC) $(FLAGS) -c allocator.cpp -o alloc.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o test
