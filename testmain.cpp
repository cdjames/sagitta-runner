#include <iostream>
#include "GameManager.hpp"
#include "MenuManager.hpp"
#include "NetworkManager.hpp"
#include "SagittaTypes.hpp"

int main()
{
	srand(std::time(0));
	NetworkManager NM = NetworkManager();
	// NM.getPlayerNumber();
	printf("There are %d players right now.\n", NM.getNumberOfPlayers());
	struct Coord c_ship;
	c_ship.x = 123;
	c_ship.y = 34;
	while(NM.getNumberOfPlayers() != 2){
		printf("looking for one more player....\n");
	}

	NM.sendCoord(c_ship, 155);
	c_ship = NM.getPosition();
	printf("c_ship x = %d\n", c_ship.x);
	printf("c_ship y = %d\n", c_ship.y);

	printf("this is player # %d", NM.getPlayerNumber());

	NM.gameOver(5);
	// printf("number of players after disconnect: %d\n", NM.getNumberOfPlayers());
	while(NM.getNumberOfPlayers() < 3) {
		//
	}
	return 0;
}