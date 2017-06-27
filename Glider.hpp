/*********************************************************************
** Author: Collin James
** Date: 10/1/15
** Description: A class from which uses the Cell base class to build 
** Conway cells. Adds extra functions to base class.
*********************************************************************/

#ifndef GLIDER_HPP
#define GLIDER_HPP

#include "Cell.hpp"

class Glider: public Cell
{
private:
	void initArrays();
	void updateCycle();
	
public:
	Glider();
	Glider(int x, int y, int size);
	~Glider();
	bool drawCells();
};

#endif