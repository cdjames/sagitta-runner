#ifndef OBJECTBP_HPP
#define OBJECTBP_HPP

#include <vector>
#include "SagittaTypes.hpp"

using std::vector;

class ObjectBlueprints
{
public:
	ObjectBlueprints();
	~ObjectBlueprints();

	/* creator functions for templates (call from main) */
	void createShipBlueprints();
	void createBulletBlueprints();
	void createExplosionBlueprints();
	void createObstacleBlueprints();
	void createAllBlueprints();

	/* global object templates */
	vector<ParticleCore> DEF_SHIP_BP;
	vector<ParticleCore> DEF_BULLET_BP;
	vector<ParticleCore> DEF_EXP_BP;
	vector<ParticleCore> DEF_OBST_BP;
	vector<ParticleCore> OBJECT;
	// extern vector<ParticleCore> FOOD_SHIP_BP;
	// extern vector<ParticleCore> SPORTS_SHIP_BP;

	// vector< vector<ParticleCore> > OBJECT_VARS;
	// vector< vector< vector<ParticleCore> > > OBJ_THEMES;

	vector< 			// x object types
			vector<			// y types
				vector<		// z blueprints
					vector<ParticleCore> > > > OBJ_BLPRNTS; // actual blueprints are vectors

	// extern vector< vector< vector<int> > > SHIP_THEMES;

};
#endif