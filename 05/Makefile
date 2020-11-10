CC = g++
FLAGS = -std=c++17 -Wall -fsanitize=address

all: test_pre 

test: test_pre
	./test_pre

test_pre: serializer.o test.o
	$(CC) $(FLAGS) -o test_pre serializer.o test.o

alloc.o: serializer.cpp
	$(CC) $(FLAGS) -c serializer.cpp -o serializer.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -f *.o test_pre
