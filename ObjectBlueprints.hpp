#ifndef OBJECTBP_HPP
#define OBJECTBP_HPP

#include <vector>
#include "SagittaTypes.hpp"

using std::vector;

/* creator functions for templates (call from main) */
void createShipBlueprints();

/* global object templates */
extern vector<ParticleCore> DEF_SHIP_BP;
extern vector< vector<ParticleCore> > DEF_OBST_BP;


// extern vector< vector< vector<int> > > SHIP_THEMES;

#endif