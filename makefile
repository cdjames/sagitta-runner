
# on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

OPS = -std=c++11
OPS += -g 
OPS += -Wall 

OPS_NC = -lncurses
OPS_NC += ${OPS}

CXX = main.cpp
CXX += GameManager.cpp

PROG1 = runner

default: runner

ObjectBlueprints.o:
	g++ -c ObjectBlueprints.cpp ${OPS}

Object.o:
	g++ -c Object.cpp ${OPS_NC}

GameManager.o:
	g++ -c GameManager.cpp ${OPS_NC}

runner: clean GameManager.o Object.o ObjectBlueprints.o
	g++ main.cpp GameManager.o Object.o ObjectBlueprints.o -o ${PROG1} ${OPS_NC}

clean:
	rm -f a.out *.o *~ ${PROG1}
