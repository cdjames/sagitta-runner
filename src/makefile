# on unix-y systems, type 'make'.
# if that doesn't work, 'make -f makefile' might be useful.

OPS = -std=c++11
# OPS += -g 
# OPS += -ggdb
# OPS += -Wall 

OPS_NC = -lncurses
# OPS_NC += -lpthread
OPS_NC += ${OPS}

CXX = main.cpp
CXX += GameManager.cpp

PROG1 = runner

default: testing

ObjectBlueprints.o:
	g++ -c ObjectBlueprints.cpp ${OPS}

cj_random.o:
	g++ -c cj_random.cpp ${OPS}

Object.o:
	g++ -c Object.cpp ${OPS_NC}

Ship.o:
	g++ -c Ship.cpp ${OPS_NC}

Obstacle.o:
	g++ -c Obstacle.cpp ${OPS_NC}

Bullet.o:
	g++ -c Bullet.cpp ${OPS_NC}

Explosion.o:
	g++ -c Explosion.cpp ${OPS_NC}

GameManager.o:
	g++ -c GameManager.cpp ${OPS_NC}

MenuManager.o:
	g++ -c MenuManager.cpp ${OPS_NC}

NetworkManager.o:
	g++ -c NetworkManager.cpp ${OPS_NC}

server: cleanServer
	g++ server.cpp -o server ${OPS}
	cp -i server ../binaries/server

runner: Object.o Ship.o Obstacle.o Bullet.o Explosion.o ObjectBlueprints.o GameManager.o MenuManager.o NetworkManager.o cj_random.o
	g++ main.cpp GameManager.o MenuManager.o NetworkManager.o Object.o Ship.o Obstacle.o Bullet.o Explosion.o ObjectBlueprints.o cj_random.o -o ${PROG1} ${OPS_NC}

testing: clean runner moveBin

clean:
	rm -f a.out *.o *~ ${PROG1}

cleanServer:
	rm -f server

moveBin:
	cp -i ${PROG1} ../binaries/${PROG1}
	
