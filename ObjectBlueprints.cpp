#include "ObjectBlueprints.hpp"


void createShipBlueprints() {
	/* create for theme 0 */
	DEF_SHIP_BP.push_back( ParticleCore { Coord {3, 5} , 0, 0} ); // first line is the height and width
	DEF_SHIP_BP.push_back( ParticleCore { Coord {1, 0}, '\\', 1} ); // then x, y, symbol, color
	DEF_SHIP_BP.push_back( ParticleCore { Coord {2, 0}, '\\', 1} );
	DEF_SHIP_BP.push_back( ParticleCore { Coord {0, 1}, '}', 7} );
	DEF_SHIP_BP.push_back( ParticleCore { Coord {1, 1}, '=', 7} );
	DEF_SHIP_BP.push_back( ParticleCore { Coord {2, 1}, 'x', 1} );
	DEF_SHIP_BP.push_back( ParticleCore { Coord {3, 1}, '=', 7} );
	DEF_SHIP_BP.push_back( ParticleCore { Coord {4, 1}, '>', 7} );
	DEF_SHIP_BP.push_back( ParticleCore { Coord {1, 2}, '/', 1} );
	DEF_SHIP_BP.push_back( ParticleCore { Coord {2, 2}, '/', 1} );

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_SHIP_BP);
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	SHIP_THEMES.at(SPACE) = OBJECT_VARS;

	/* clear the vars array to reuse */
	vector< vector<ParticleCore> > ().swap(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	OBJECT_VARS.push_back(DEF_SHIP_BP);
	SHIP_THEMES.at(FOOD) = OBJECT_VARS;
	vector< vector<ParticleCore> > ().swap(OBJECT_VARS);

	OBJECT_VARS.push_back(DEF_SHIP_BP);
	SHIP_THEMES.at(SPORTS) = OBJECT_VARS;
	vector< vector<ParticleCore> > ().swap(OBJECT_VARS);

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.at(SHIP) = SHIP_THEMES;

}

void createAllBlueprints() {
	// OBJ_BLPRNTS = vector< vector< vector< vector<ParticleCore> > > > (NUM_TYPES, 
	// 					vector< vector< vector<ParticleCore> > > (NUM_THEMES,
	// 					vector< vector<ParticleCore> > ));
	// for (int i = 0; i < NUM_TYPES; i++)
	// {
	// 	for (int i = 0; i < NUM_THEMES; i++)
	// 	{
	// 		/* code */
	// 	}
	// }
}

vector<ParticleCore> DEF_SHIP_BP;
// vector<ParticleCore> FOOD_SHIP_BP;
// vector<ParticleCore> SPORTS_SHIP_BP;
vector<ParticleCore> OBJECT;
vector< vector<ParticleCore> > OBJECT_VARS;
vector< vector< vector<ParticleCore> > > SHIP_THEMES (SPORTS+1);

vector< 			// x object types
		vector<			// y types
			vector<		// z blueprints
				vector<ParticleCore> > > > OBJ_BLPRNTS (OBSTACLE+1);
// vector< vector<int> > DEF_OBST_BP (5, vector<int> (4, ));
// vector< vector<int> > DEF_OBST_BP = {
// 	{3, 3, -1, -1}, // first line is the height and width
// 	{1, 0, 'x', 1}, // then x, y, symbol, color
// 	{0, 1, 'X', 2},
// 	{2, 1, 'x', 3},
// 	{1, 2, 'X', 4}
// };

// /* number of themes in vector should equal the number of theme types in SagittaTypes */
// vector< vector< vector<int> > > SHIP_THEMES = {
// 	def_ship_bp,
// 	def_ship_bp,
// 	def_ship_bp
// };
