#include "ObjectBlueprints.hpp"

vector< vector<int> > DEF_SHIP_BP = {
	{3, 5, -1, -1}, // first line is the height and width
	{1, 0, '\\', 1}, // then x, y, symbol, color
	{2, 0, '\\', 1},
	{0, 1, '}', 7},
	{1, 1, '=', 7},
	{2, 1, 'x', 1},
	{3, 1, '=', 7},
	{4, 1, '>', 7},
	{1, 2, '/', 1},
	{2, 2, '/', 1}
};

vector< vector<int> > DEF_OBST_BP = {
	{3, 3, -1, -1}, // first line is the height and width
	{1, 0, 'x', 1}, // then x, y, symbol, color
	{0, 1, 'X', 2},
	{2, 1, 'x', 3},
	{1, 2, 'X', 4}
};

/* number of themes in vector should equal the number of theme types in SagittaTypes */
vector< vector< vector<int> > > SHIP_THEMES = {
	DEF_SHIP_BP,
	DEF_SHIP_BP,
	DEF_SHIP_BP
};
