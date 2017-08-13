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

	NM.sendCoord(35, NM.getPlayerNumber());
	

	NM.gameOver(5);
	// printf("number of players after disconnect: %d\n", NM.getNumberOfPlayers());
	while(NM.getNumberOfPlayers() < 3) {
		//
	}
	return 0;
}