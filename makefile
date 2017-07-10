
# on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

OPS = -lncurses
OPS += -std=c++11
OPS += -g 
OPS += -Wall 

CXX = main.cpp
CXX += GameManager.cpp

PROG1 = runner

Object.o:
	g++ ${OPS} -c Object.cpp

GameManager.o:
	g++ ${OPS} -c GameManager.cpp

runner: clean GameManager.o Object.o
	g++ ${OPS} main.cpp GameManager.o Object.o -o ${PROG1}

default:
	g++ ${OPS} ${CXX} -o ${PROG1}

clean:
	rm -f a.out *.o *~ ${PROG1}
