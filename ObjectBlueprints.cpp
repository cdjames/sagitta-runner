#include "ObjectBlueprints.hpp"
#include <iostream>

vector<ParticleCore> DEF_SHIP_BP;
vector<ParticleCore> DEF_BULLET_BP;
vector<ParticleCore> DEF_EXP_BP;
vector<ParticleCore> DEF_OBST_BP;
// vector<ParticleCore> OBJECT;
vector< 			// x object types
	vector<			// y theme types
		vector<		// z blueprints
			vector<ParticleCore> // a single blueprint
			> > > OBJ_BLPRNTS;

void createShipBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES;
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

	/* create for theme 0 */
	DEF_SHIP_BP.push_back( ParticleCore { Coord {3, 5} , 0, 6} ); // first line is the height and width
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
	// std::cout << "ship, space, first symbol=" << OBJECT_VARS[0][1].symbol << std::endl;
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);


	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_SHIP_BP);
	OBJ_THEMES.push_back(OBJECT_VARS2);


	OBJECT_VARS3.push_back(DEF_SHIP_BP);
	OBJ_THEMES.push_back(OBJECT_VARS3);
	// std::cout << "ship, space, first symbol=" << OBJ_THEMES[0][0][1].symbol << std::endl;

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);
	// std::cout << "ship, space, first symbol=" << OBJ_BLPRNTS[0][0][0][1].symbol << std::endl;

	/* clear the OBJ_THEMES array to reuse */
	// resizeObjThemes();

}

void createBulletBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES;
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
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_BULLET_BP);
	OBJ_THEMES.push_back(OBJECT_VARS2);

	OBJECT_VARS3.push_back(DEF_BULLET_BP);
	OBJ_THEMES.push_back(OBJECT_VARS3);

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);

}

void createExplosionBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES;
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

	/* create for theme 0 */
	DEF_EXP_BP.push_back( ParticleCore { Coord {3, 3}, 0, 0} ); // first line is the height and width
	DEF_EXP_BP.push_back( ParticleCore { Coord {0, 1}, '*', 11} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 0}, '*', 9} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 1}, '*', 166} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {2, 1}, '*', 9} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 2}, '*', 11} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_EXP_BP);
	// push more variations if necessary
	vector<ParticleCore> exp_2;
	exp_2.push_back( ParticleCore { Coord {3, 3}, 0, 0} ); // first line is the height and width
	exp_2.push_back( ParticleCore { Coord {0, 0}, '*', 11} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {2, 0}, '*', 9} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {1, 1}, '*', 166} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {2, 2}, '*', 9} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {0, 2}, '*', 11} ); // then x, y, symbol, color

	OBJECT_VARS.push_back(exp_2);
	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* clear the vars array to reuse */
	vector< vector<ParticleCore> > ().swap(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	vector<ParticleCore> ship_exp;
	ship_exp.push_back( ParticleCore { Coord {3, 5}, 0, 0} ); // first line is the height and width
	ship_exp.push_back( ParticleCore { Coord {2, 0}, '*', 11} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {1, 1}, '*', 11} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {3, 1}, '*', 9} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {2, 1}, '*', 166} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {3, 2}, ' ', 9} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {1, 2}, ' ', 11} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {2, 2}, '*', 11} ); // then x, y, symbol, color

	vector<ParticleCore> ship_exp_2;
	ship_exp_2.push_back( ParticleCore { Coord {3, 5}, 0, 0} ); // first line is the height and width
	ship_exp_2.push_back( ParticleCore { Coord {1, 0}, '*', 11} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {3, 0}, '*', 9} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {0, 1}, '*', 166} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {2, 1}, '*', 9} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {4, 1}, '*', 166} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {3, 2}, '*', 9} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {1, 2}, '*', 11} ); // then x, y, symbol, color

	OBJECT_VARS2.push_back(ship_exp);
	OBJECT_VARS2.push_back(ship_exp_2);
	OBJ_THEMES.push_back(OBJECT_VARS2);

	OBJECT_VARS3.push_back(DEF_EXP_BP);
	OBJECT_VARS3.push_back(exp_2);
	OBJ_THEMES.push_back(OBJECT_VARS3);

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);

}

void createObstacleBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES;
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

	/* create for theme 0 */
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 1}, 0, 0} ); // first line is the height and width
	DEF_OBST_BP.push_back( ParticleCore { Coord {0, 1}, '<', 5} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 0}, '/', 14} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 1}, '=', 5} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {2, 1}, '[', 15} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 2}, '\\', 14} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_OBST_BP);
	// push more variations if necessary
	vector<ParticleCore> space_obst_2;
	space_obst_2.push_back( ParticleCore { Coord {7, 5}, 0, 3} );
	space_obst_2.push_back( ParticleCore { Coord {0, 0}, '/', 7} );
	space_obst_2.push_back( ParticleCore { Coord {0, 1}, '|', 7} );
	space_obst_2.push_back( ParticleCore { Coord {0, 2}, '|', 7} );
	space_obst_2.push_back( ParticleCore { Coord {0, 3}, '|', 7} );
	space_obst_2.push_back( ParticleCore { Coord {0, 4}, '\\', 7} );
	space_obst_2.push_back( ParticleCore { Coord {1, 2}, '=', 8} );
	space_obst_2.push_back( ParticleCore { Coord {2, 1}, '/', 15} );
	space_obst_2.push_back( ParticleCore { Coord {2, 2}, '|', 15} );
	space_obst_2.push_back( ParticleCore { Coord {2, 3}, '\\', 15} );
	space_obst_2.push_back( ParticleCore { Coord {3, 1}, '^', 15} );
	space_obst_2.push_back( ParticleCore { Coord {3, 2}, 'O', 8} );
	space_obst_2.push_back( ParticleCore { Coord {3, 3}, '_', 15} );
	space_obst_2.push_back( ParticleCore { Coord {4, 1}, '\\', 15} );
	space_obst_2.push_back( ParticleCore { Coord {4, 2}, '|', 15} );
	space_obst_2.push_back( ParticleCore { Coord {4, 3}, '/', 15} );
	space_obst_2.push_back( ParticleCore { Coord {5, 2}, '=', 8} );
	space_obst_2.push_back( ParticleCore { Coord {6, 0}, '\\', 7} );
	space_obst_2.push_back( ParticleCore { Coord {6, 1}, '|', 7} );
	space_obst_2.push_back( ParticleCore { Coord {6, 2}, '|', 7} );
	space_obst_2.push_back( ParticleCore { Coord {6, 3}, '|', 7} );
	space_obst_2.push_back( ParticleCore { Coord {6, 4}, '/', 7} );
	OBJECT_VARS.push_back(space_obst_2);
	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_OBST_BP);
	OBJECT_VARS2.push_back(space_obst_2);
	OBJ_THEMES.push_back(OBJECT_VARS2);

	OBJECT_VARS3.push_back(DEF_OBST_BP);
	OBJECT_VARS3.push_back(space_obst_2);
	OBJ_THEMES.push_back(OBJECT_VARS3);

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);

}

void createAllBlueprints() {
	createShipBlueprints();
	createBulletBlueprints();
	createExplosionBlueprints();
	createObstacleBlueprints();
	// std::cout << "ship, space, first size=" << OBJ_BLPRNTS[0][0][0].size() << std::endl;
}
