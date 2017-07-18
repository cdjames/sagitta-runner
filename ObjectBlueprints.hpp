#ifndef OBJECTBP_HPP
#define OBJECTBP_HPP

#include <vector>
#include "SagittaTypes.hpp"

using std::vector;

/* creator functions for templates (call from main) */
void createShipBlueprints();
void createBulletBlueprints();
void createExplosionBlueprints();
void createObstacleBlueprints();
void createAllBlueprints();
void resizeObjThemes();

/* global object templates */
extern vector<ParticleCore> DEF_SHIP_BP;
extern vector<ParticleCore> DEF_BULLET_BP;
extern vector<ParticleCore> DEF_EXP_BP;
extern vector<ParticleCore> DEF_OBST_BP;
extern vector<ParticleCore> OBJECT;
// extern vector<ParticleCore> FOOD_SHIP_BP;
// extern vector<ParticleCore> SPORTS_SHIP_BP;

extern vector< vector<ParticleCore> > OBJECT_VARS;
extern vector< vector< vector<ParticleCore> > > OBJ_THEMES;

extern vector< 			// x object types
		vector<			// y types
			vector<		// z blueprints
				vector<ParticleCore> > > > OBJ_BLPRNTS; // actual blueprints are vectors

// extern vector< vector< vector<int> > > SHIP_THEMES;

#endif