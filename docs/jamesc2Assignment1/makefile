# to execute the makefile on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

# replace 'your_file' below with your actual source file names.
# add more if needed.

OPS = -lncurses

CXX = Cell.cpp
CXX += Oscillator.cpp
CXX += Glider.cpp
CXX += Gun.cpp
CXX += main.cpp

PROG1 = main

default:
	g++ ${OPS} ${CXX} -o ${PROG1}

clean:
	rm -f a.out *.o *~ ${PROG1}