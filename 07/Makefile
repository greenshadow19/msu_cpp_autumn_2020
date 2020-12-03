CXX=g++
CXXFLAGS=-std=c++11 -Wall -fsanitize=address

all: test_pre 

test: test_pre
	./test_pre

test_pre: test.o
	$(CXX) test.o $(CXXFLAGS) -o test_pre 

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f *.o test_pre
