
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

MenuManager.o: clean
	g++ -c MenuManager.cpp ${OPS}

runner: clean GameManager.o Object.o MenuManager.o
	g++ main.cpp GameManager.o Object.o MenuManager.o -o ${PROG1} ${OPS}

clean:
	rm -f a.out *.o *~ ${PROG1}
