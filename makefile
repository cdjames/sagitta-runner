
# on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

OPS = -lncurses
OPS += -g 
OPS += -Wall 
OPS += -std=c++11

CXX = main.cpp
CXX += GameManager.cpp

PROG1 = runner

GameManager.o:
	g++ ${OPS} -c GameManager.cpp

runner: GameManager.o
	g++ ${OPS} main.cpp GameManager.o -o ${PROG1}

default:
	g++ ${OPS} ${CXX} -o ${PROG1}

clean:
	rm -f a.out *.o *~ ${PROG1}
