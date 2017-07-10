
# on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

OPS = -lncurses
OPS += -std=c++11

CXX = main.cpp
CXX += GameManager.cpp

PROG1 = runner

default:
	g++ ${OPS} ${CXX} -o ${PROG1}

clean:
	rm -f a.out *.o *~ ${PROG1}
