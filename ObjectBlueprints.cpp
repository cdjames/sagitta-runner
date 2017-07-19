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
	std::cout << "ship, space, first symbol=" << OBJECT_VARS[0][1].symbol << std::endl;
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);


	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_SHIP_BP);
	OBJ_THEMES.push_back(OBJECT_VARS2);


	OBJECT_VARS3.push_back(DEF_SHIP_BP);
	OBJ_THEMES.push_back(OBJECT_VARS3);
	std::cout << "ship, space, first symbol=" << OBJ_THEMES[0][0][1].symbol << std::endl;

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);
	std::cout << "ship, space, first symbol=" << OBJ_BLPRNTS[0][0][0][1].symbol << std::endl;

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
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* clear the vars array to reuse */
	vector< vector<ParticleCore> > ().swap(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_EXP_BP);
	OBJ_THEMES.push_back(OBJECT_VARS2);

	OBJECT_VARS3.push_back(DEF_EXP_BP);
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
	DEF_OBST_BP.push_back( ParticleCore { Coord {0, 1}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 0}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 1}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {2, 1}, '+', 8} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 2}, '+', 8} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_OBST_BP);
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	OBJECT_VARS2.push_back(DEF_OBST_BP);
	OBJ_THEMES.push_back(OBJECT_VARS2);

	OBJECT_VARS3.push_back(DEF_OBST_BP);
	OBJ_THEMES.push_back(OBJECT_VARS3);

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);

}

void createAllBlueprints() {
	createShipBlueprints();
	createBulletBlueprints();
	createExplosionBlueprints();
	createObstacleBlueprints();
}
