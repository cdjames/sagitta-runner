#include "ObjectBlueprints.hpp"

ObjectBlueprints::ObjectBlueprints() {
	// vector< vector< vector<ParticleCore> > > OBJ_THEMES.resize(SPORTS+1);
	vector< 			// x object types
		vector<			// y theme types
			vector<		// z blueprints
				vector<ParticleCore> // a single blueprint
				> > > OBJ_BLPRNTS(OBSTACLE+1);
	createAllBlueprints();
}

ObjectBlueprints::~ObjectBlueprints() {}

void ObjectBlueprints::createShipBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES(SPORTS+1);
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

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
	OBJ_THEMES.at(SPACE) = OBJECT_VARS;


	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_SHIP_BP);
	OBJ_THEMES.at(FOOD) = OBJECT_VARS2;


	OBJECT_VARS3.push_back(DEF_SHIP_BP);
	OBJ_THEMES.at(SPORTS) = OBJECT_VARS3;

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.at(SHIP) = OBJ_THEMES;

	/* clear the OBJ_THEMES array to reuse */
	// resizeObjThemes();

}

void ObjectBlueprints::createBulletBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES(SPORTS+1);
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

	/* create for theme 0 */
	DEF_BULLET_BP.push_back( ParticleCore { Coord {1, 1} , 0, 0} ); // first line is the height and width
	DEF_BULLET_BP.push_back( ParticleCore { Coord {0, 0}, '*', 166} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_BULLET_BP);
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.at(SPACE) = OBJECT_VARS;

	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_BULLET_BP);
	OBJ_THEMES.at(FOOD) = OBJECT_VARS2;

	OBJECT_VARS3.push_back(DEF_BULLET_BP);
	OBJ_THEMES.at(SPORTS) = OBJECT_VARS3;

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.at(BULLET) = OBJ_THEMES;

}

void ObjectBlueprints::createExplosionBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES(SPORTS+1);
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

	/* create for theme 0 */
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 1}, 0, 0} ); // first line is the height and width
	DEF_EXP_BP.push_back( ParticleCore { Coord {0, 1}, '*', 11} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 0}, '*', 9} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 1}, '*', 166} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {2, 1}, '*', 9} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 2}, '*', 11} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_EXP_BP);
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.at(SPACE) = OBJECT_VARS;

	/* clear the vars array to reuse */
	vector< vector<ParticleCore> > ().swap(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_EXP_BP);
	OBJ_THEMES.at(FOOD) = OBJECT_VARS2;

	OBJECT_VARS3.push_back(DEF_EXP_BP);
	OBJ_THEMES.at(SPORTS) = OBJECT_VARS3;

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.at(BULLET) = OBJ_THEMES;

}

void ObjectBlueprints::createObstacleBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES(SPORTS+1);
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

	/* create for theme 0 */
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 1}, 0, 0} ); // first line is the height and width
	DEF_OBST_BP.push_back( ParticleCore { Coord {0, 1}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 0}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 1}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {2, 1}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 2}, '+', 8} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_OBST_BP);
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.at(SPACE) = OBJECT_VARS;

	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_OBST_BP);
	OBJ_THEMES.at(FOOD) = OBJECT_VARS2;

	OBJECT_VARS3.push_back(DEF_OBST_BP);
	OBJ_THEMES.at(SPORTS) = OBJECT_VARS3;

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.at(BULLET) = OBJ_THEMES;

}

void ObjectBlueprints::createAllBlueprints() {
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
	createShipBlueprints();
	createBulletBlueprints();
	createExplosionBlueprints();
	createObstacleBlueprints();
}

// vector< vector<int> > DEF_OBST_BP (5, vector<int> (4, ));
// vector< vector<int> > DEF_OBST_BP = {
// 	{3, 3, -1, -1}, // first line is the height and width
// 	{1, 0, 'x', 1}, // then x, y, symbol, color
// 	{0, 1, 'X', 2},
// 	{2, 1, 'x', 3},
// 	{1, 2, 'X', 4}
// };

// /* number of themes in vector should equal the number of theme types in SagittaTypes */
// vector< vector< vector<int> > > OBJ_THEMES = {
// 	def_ship_bp,
// 	def_ship_bp,
// 	def_ship_bp
// };
