/*********************************************************************
** Author: Collin James
** Date: 10/1/15
** Description: A class from which uses the Cell base class to build 
** a Conway oscillator cell. Adds extra functions to base class.
*********************************************************************/

#ifndef OSCILLATOR_HPP
#define OSCILLATOR_HPP

#include "Cell.hpp"

class Oscillator: public Cell
{
private:
	void initArrays();
	void updateCycle();

public:
	Oscillator();
	Oscillator(int x, int y, int size);
	~Oscillator();
	bool drawCells();
};

#endif