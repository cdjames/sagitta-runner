/*********************************************************************
** Author: Collin James
** Date: 10/1/15
** Description: Main routines for Conway's game simulator
*********************************************************************/

#include <iostream>
#include "Oscillator.hpp"
#include "Glider.hpp"
#include "Gun.hpp"
#include <curses.h>
// #include <stdlib.h>
void getUserPrefs(char &pref, int &x, int &y);

int main()
{
	char prefs = 'o',
		 ch; // for while loop
	int x = 0, 
		y = 0;
	/* set pointers to null and use if statements when deleting to avoid
	 * segmentation fault on flip */
	Oscillator* myOsc = NULL;
	Glider* myGlider = NULL;
	Gun* myGun = NULL;

	getUserPrefs(prefs, x, y);

	/* decide which cell to instantiate */
	switch (prefs)
	{
		case 'g':
			myGlider = new Glider(x, y, 4); // 4 is the size of the array in the class
			myGlider->initWindow(2, 0);	// starts ncurses mode and draws box
			break;
		case 'c':
			myGun = new Gun(x, y, 38);
			myGun->initWindow(2, 0);	// starts ncurses mode and draws box
			break;
		default: // 'o' or anything else
			myOsc = new Oscillator(x, y, 3);
			myOsc->initWindow(2, 0);		// starts ncurses mode and draws box
	}
	
	/* draw the cells; quit only when 'q' is pressed */
	do
	{
		switch (prefs){
			case 'g':
				myGlider->drawCells();
				break;
			case 'c':
				myGun->drawCells();	
				break;
			default: // 'o' or anything else
				myOsc->drawCells();
		}
	} while ((ch = getch()) != 'q'); // loop until the user enters 'q'

	/* clean up pointers before exit. Only do this if the pointer was
	 * actually used */
	if(myOsc != NULL)
	{
		delete myOsc; 	
		myOsc = 0;
	}
	if(myGlider != NULL)
	{
		delete myGlider; 	
		myGlider = 0;
	}
	if(myGun != NULL)
	{
		delete myGun; 	
		myGun = 0;
	}

	return 0;
}

/*********************************************************************
** Description: 
** Get the preference for type of cell, starting x and y
*********************************************************************/
void getUserPrefs(char &pref, int &x, int &y)
{
	std::cout 	<< "What kind of cell to start with?\n'o' for Oscillator, 'g' for Glider, 'c' for Gun"
				<< std::endl;
	/* accept input only if o, g, or c */
	do
		std::cin >> pref;
	while (pref != 'o' && pref != 'g' && pref != 'c');

	std::cout	<< "Choose x/y coordinates for cell."
				<<	"\nX range is between 0 and 39. Y range is between 0 and 19."
				<<	"\n"
				<< "Choose x" << std::endl;
	std::cin >> x;
	std::cout 	<< "Choose y" << std::endl;
	std::cin >> y;
}