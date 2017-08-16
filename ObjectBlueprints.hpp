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
void readFromRandFile(const char * fname, std::vector<int> * v);


/* global object templates */
extern vector<ParticleCore> DEF_SHIP_BP;
extern vector<ParticleCore> DEF_BULLET_BP;
extern vector<ParticleCore> DEF_EXP_BP;
extern vector<ParticleCore> DEF_OBST_BP;

extern vector< 			// x object types
		vector<			// y types
			vector<		// z blueprints
				vector<ParticleCore> > > > OBJ_BLPRNTS; // actual blueprints are vectors

void cj_srand(int seed);
int cj_rand();
extern vector<int> rand_num_list;
extern int cj_rand_seed;
extern int cj_rand_max;

#endif
