
# on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

OPS = -lncurses
OPS += -std=c++11
OPS += -g 
OPS += -Wall 

CXX = main.cpp
CXX += GameManager.cpp

PROG1 = runner

default: runner

Object.o: clean
	g++ -c Object.cpp ${OPS}

GameManager.o: clean
	g++ -c GameManager.cpp ${OPS}

runner: clean GameManager.o Object.o
	g++ main.cpp GameManager.o Object.o -o ${PROG1} ${OPS}

clean:
	rm -f a.out *.o *~ ${PROG1}
