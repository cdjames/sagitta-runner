/*********************************************************************
** Author: Collin James
** Date: 10/1/15
** Description: A class from which uses the Cell base class to build 
** Conway cells. Adds extra functions to base class.
*********************************************************************/

#ifndef GUN_HPP
#define GUN_HPP

#include "Cell.hpp"

class Gun: public Cell
{
private:
	void initArrays();
	void updateCycle();
	
public:
	Gun();
	Gun(int x, int y, int size);
	~Gun();
	bool drawCells();
};

#endif