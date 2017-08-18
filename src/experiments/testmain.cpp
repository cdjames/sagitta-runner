#include <iostream>
#include "GameManager.hpp"
#include "MenuManager.hpp"
#include "NetworkManager.hpp"
#include "SagittaTypes.hpp"

int main()
{
	srand(std::time(0));
	NetworkManager NM = NetworkManager();
	printf("player = %d\n", NM.getPlayerNumber());
	// printf("There are %d players right now.\n", NM.getNumberOfPlayers());

	// while(NM.getNumberOfPlayers() != 2){
	// 	printf("looking for one more player....\n");
	// }

	NM.sendCoord(35, NM.getPlayerNumber());
	printf("%d\n", NM.getCoord(NM.getPlayerNumber()));
	NM.sendCoord(35, NM.getPlayerNumber());
	

	NM.gameOver();
	// printf("number of players after disconnect: %d\n", NM.getNumberOfPlayers());
	while(NM.getNumberOfPlayers() < 3) {
		//
	}
	return 0;
}