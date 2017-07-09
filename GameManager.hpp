/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: The managing class of the infinite runner
*********************************************************************/

#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <curses.h>
#include <vector>
#include "SagittaTypes.hpp"

class GameManager
{
protected:
	WINDOW * win;
	std::vector<ObjectType> gameboard;
	
public:
	GameManager();
	~GameManager();
};

#endif