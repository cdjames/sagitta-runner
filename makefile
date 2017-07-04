
# on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

OPS = -lncurses

CXX = Drawer.cpp
CXX += Oscillator.cpp
# CXX += Glider.cpp
# CXX += Gun.cpp
CXX += main.cpp

PROG1 = runner

default:
	g++ ${OPS} ${CXX} -o ${PROG1}

clean:
	rm -f a.out *.o *~ ${PROG1}
