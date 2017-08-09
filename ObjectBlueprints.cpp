#include "ObjectBlueprints.hpp"
#include <iostream>
#include <fstream>

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

vector<int> RAND_NUM_LIST;
int CJ_RAND_SEED;

void readFromRandFile(const char * fname, std::vector<int> * v) { // help here https://stackoverflow.com/questions/14516915/read-numeric-data-from-a-text-file-in-c#14517130
	std::fstream f(fname, std::ios_base::in);
	int val;
	while(f >> val)
		v->push_back(val);
	// std::cout << (*v)[v->size()-1] << std::endl;
}

void cj_srand(int seed) {
	CJ_RAND_SEED = seed;
}

int cj_rand() {
	int num = RAND_NUM_LIST[CJ_RAND_SEED];
	if(CJ_RAND_SEED < CJ_RAND_MAX)
		CJ_RAND_SEED++;
	else
		CJ_RAND_SEED = 0;
	return num;
}

void createShipBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES;
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;

	/* create for theme 0 */
	DEF_SHIP_BP.push_back( ParticleCore { Coord {3, 5} , 0, 6} ); // first line is the height, width, value, and index of the "front" of the object
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

	/* create for SPACE theme */
	DEF_BULLET_BP.push_back( ParticleCore { Coord {1, 1} , 0, 0} ); // first line is the height and width
	DEF_BULLET_BP.push_back( ParticleCore { Coord {0, 0}, '*', 166} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_BULLET_BP);
	// push more variations if necessary

	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	vector<ParticleCore> food_bullet_1;
	food_bullet_1.push_back( ParticleCore { Coord {1, 1} , 0, 0} ); // first line is the height and width
	food_bullet_1.push_back( ParticleCore { Coord {0, 0}, '@', 214} ); // then x, y, symbol, color
	OBJECT_VARS2.push_back(food_bullet_1);
	OBJ_THEMES.push_back(OBJECT_VARS2);

	vector<ParticleCore> sport_bullet_1;
	sport_bullet_1.push_back( ParticleCore { Coord {1, 1} , 0, 0} ); // first line is the height and width
	sport_bullet_1.push_back( ParticleCore { Coord {0, 0}, '~', 124} ); // then x, y, symbol, color
	OBJECT_VARS3.push_back(sport_bullet_1);
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
	DEF_EXP_BP.push_back( ParticleCore { Coord {0, 1}, '*', 178} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 0}, '*', 160} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 1}, '*', 11} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {2, 1}, '*', 172} ); // then x, y, symbol, color
	DEF_EXP_BP.push_back( ParticleCore { Coord {1, 2}, '*', 202} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_EXP_BP);
	// push more variations if necessary
	vector<ParticleCore> exp_2;
	exp_2.push_back( ParticleCore { Coord {3, 3}, 0, 0} ); // first line is the height and width
	exp_2.push_back( ParticleCore { Coord {0, 0}, '*', 11} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {2, 0}, '*', 178} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {1, 1}, '*', 160} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {2, 2}, '*', 202} ); // then x, y, symbol, color
	exp_2.push_back( ParticleCore { Coord {0, 2}, '*', 172} ); // then x, y, symbol, color

	OBJECT_VARS.push_back(exp_2);
	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* clear the vars array to reuse */
	vector< vector<ParticleCore> > ().swap(OBJECT_VARS);

	/* create more items for each them or just push existing item */
	vector<ParticleCore> ship_exp;
	ship_exp.push_back( ParticleCore { Coord {3, 5}, 0, 0} ); // first line is the height and width
	ship_exp.push_back( ParticleCore { Coord {2, 0}, '*', 9} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {1, 1}, '*', 178} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {3, 1}, '*', 160} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {2, 1}, '*', 166} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {3, 2}, ' ', 202} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {1, 2}, ' ', 172} ); // then x, y, symbol, color
	ship_exp.push_back( ParticleCore { Coord {2, 2}, '*', 11} ); // then x, y, symbol, color

	vector<ParticleCore> ship_exp_2;
	ship_exp_2.push_back( ParticleCore { Coord {3, 5}, 0, 0} ); // first line is the height and width
	ship_exp_2.push_back( ParticleCore { Coord {1, 0}, '*', 178} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {3, 0}, '*', 160} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {0, 1}, '*', 166} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {2, 1}, ' ', 202} ); // then x, y, symbol, color
	ship_exp_2.push_back( ParticleCore { Coord {4, 1}, '*', 172} ); // then x, y, symbol, color
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
	/* small ship 

	      / 
         <=[
          \
     */
	DEF_OBST_BP.push_back( ParticleCore { Coord {3, 3}, 0, 0} ); // first line is the height and width
	DEF_OBST_BP.push_back( ParticleCore { Coord {0, 1}, '<', 5} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 0}, '/', 14} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 1}, '=', 5} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {2, 1}, '[', 15} ); // then x, y, symbol, color
	DEF_OBST_BP.push_back( ParticleCore { Coord {1, 2}, '\\', 14} ); // then x, y, symbol, color

	/* add to themes array */
	OBJECT_VARS.push_back(DEF_OBST_BP);
	// push more variations if necessary

	/* big ship 

	/     \
    | /^\ |            
    |=|O|=|            
    | \_/ |            
    \     /

	*/
	vector<ParticleCore> space_obst_2; // big ship
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

	/* stealth ship
	      ,,,,/*  
		<(^_^(**
		  ````\*
	*/
	vector<ParticleCore> space_obst_3;
	space_obst_3.push_back( ParticleCore { Coord {3, 8}, 0, 1} );
	space_obst_3.push_back( ParticleCore { Coord {0, 1}, '<', 234} );
	space_obst_3.push_back( ParticleCore { Coord {1, 1}, '(', 235} );
	space_obst_3.push_back( ParticleCore { Coord {2, 1}, '^', 232} );
	space_obst_3.push_back( ParticleCore { Coord {3, 1}, '_', 232} );
	space_obst_3.push_back( ParticleCore { Coord {4, 1}, '^', 232} );
	space_obst_3.push_back( ParticleCore { Coord {5, 1}, '(', 235} );
	space_obst_3.push_back( ParticleCore { Coord {6, 1}, '*', 196} );
	space_obst_3.push_back( ParticleCore { Coord {7, 1}, '*', 202} );
	space_obst_3.push_back( ParticleCore { Coord {2, 0}, ',', 232} );
	space_obst_3.push_back( ParticleCore { Coord {3, 0}, ',', 233} );
	space_obst_3.push_back( ParticleCore { Coord {4, 0}, ',', 234} );
	space_obst_3.push_back( ParticleCore { Coord {5, 0}, ',', 235} );
	space_obst_3.push_back( ParticleCore { Coord {6, 0}, '/', 236} );
	space_obst_3.push_back( ParticleCore { Coord {7, 0}, '*', 178} );
	space_obst_3.push_back( ParticleCore { Coord {2, 2}, '`', 232} );
	space_obst_3.push_back( ParticleCore { Coord {3, 2}, '`', 233} );
	space_obst_3.push_back( ParticleCore { Coord {4, 2}, '`', 234} );
	space_obst_3.push_back( ParticleCore { Coord {5, 2}, '`', 235} );
	space_obst_3.push_back( ParticleCore { Coord {6, 2}, '\\', 236} );
	space_obst_3.push_back( ParticleCore { Coord {7, 2}, '*', 178} );
	OBJECT_VARS.push_back(space_obst_3);
	/* when done, push themes onto the main blueprints array */
	OBJ_THEMES.push_back(OBJECT_VARS);

	/* FOOD THEMES */
	/* kiwi */
	vector<ParticleCore> food_obst_1;
	food_obst_1.push_back( ParticleCore { Coord {3, 3}, 0, 1});
	food_obst_1.push_back( ParticleCore { Coord {0, 1}, '(', 70});
	food_obst_1.push_back( ParticleCore { Coord {1, 0}, '_', 70});
	food_obst_1.push_back( ParticleCore { Coord {1, 1}, ':', 70});
	food_obst_1.push_back( ParticleCore { Coord {1, 2}, '"', 202});
	food_obst_1.push_back( ParticleCore { Coord {2, 1}, ')', 70});
	OBJECT_VARS2.push_back(food_obst_1);

	/* apple */
	vector<ParticleCore> food_obst_2; 
	food_obst_2.push_back( ParticleCore { Coord {3, 5}, 0, 1});
	food_obst_2.push_back( ParticleCore { Coord {0, 1}, '(', 124});
	food_obst_2.push_back( ParticleCore { Coord {1, 0}, ',', 124});
	food_obst_2.push_back( ParticleCore { Coord {1, 2}, '`', 124});
	food_obst_2.push_back( ParticleCore { Coord {2, 0}, '(', 130});
	food_obst_2.push_back( ParticleCore { Coord {2, 2}, '"', 130});
	food_obst_2.push_back( ParticleCore { Coord {3, 0}, '.', 124});
	food_obst_2.push_back( ParticleCore { Coord {3, 2}, '\'', 124});
	food_obst_2.push_back( ParticleCore { Coord {4, 1}, ')', 124});
	OBJECT_VARS2.push_back(food_obst_2);

	/* pumpkin http://www.chris.com/ascii/joan/www.geocities.com/SoHo/7373/food.html#tomatosoup 
	    _)_
 	  /`/"\`\
	  \_\_/_/
	*/
	vector<ParticleCore> food_obst_3; 
	food_obst_3.push_back( ParticleCore { Coord {3, 7}, 0, 1});
	food_obst_3.push_back( ParticleCore { Coord {0, 1}, '/', 130});
	food_obst_3.push_back( ParticleCore { Coord {0, 2}, '\\', 166});
	food_obst_3.push_back( ParticleCore { Coord {1, 1}, '`', 136});
	food_obst_3.push_back( ParticleCore { Coord {1, 2}, '_', 166});
	food_obst_3.push_back( ParticleCore { Coord {2, 0}, '_', 130});
	food_obst_3.push_back( ParticleCore { Coord {2, 1}, '/', 130});
	food_obst_3.push_back( ParticleCore { Coord {2, 2}, '\\', 166});
	food_obst_3.push_back( ParticleCore { Coord {3, 0}, ')', 70});
	food_obst_3.push_back( ParticleCore { Coord {3, 1}, '"', 136});
	food_obst_3.push_back( ParticleCore { Coord {3, 2}, '_', 166});
	food_obst_3.push_back( ParticleCore { Coord {4, 0}, '_', 166});
	food_obst_3.push_back( ParticleCore { Coord {4, 1}, '\\', 166});
	food_obst_3.push_back( ParticleCore { Coord {4, 2}, '/', 202});
	food_obst_3.push_back( ParticleCore { Coord {5, 1}, '`', 130});
	food_obst_3.push_back( ParticleCore { Coord {5, 2}, '_', 202});
	food_obst_3.push_back( ParticleCore { Coord {6, 1}, '\\', 202});
	food_obst_3.push_back( ParticleCore { Coord {6, 2}, '/', 202});
	OBJECT_VARS2.push_back(food_obst_3);

	/* knife (same source as above) 
     _______
	 `-...--######
	*/
	
	vector<ParticleCore> food_obst_4; 
	food_obst_4.push_back( ParticleCore { Coord {2, 13}, 0, 1});
	food_obst_4.push_back( ParticleCore { Coord {0, 0}, '_', 15});
	food_obst_4.push_back( ParticleCore { Coord {1, 0}, '_', 255});
	food_obst_4.push_back( ParticleCore { Coord {2, 0}, '_', 254});
	food_obst_4.push_back( ParticleCore { Coord {3, 0}, '_', 253});
	food_obst_4.push_back( ParticleCore { Coord {4, 0}, '_', 252});
	food_obst_4.push_back( ParticleCore { Coord {5, 0}, '_', 251});
	food_obst_4.push_back( ParticleCore { Coord {6, 0}, '_', 250});
	food_obst_4.push_back( ParticleCore { Coord {0, 1}, '`', 255});
	food_obst_4.push_back( ParticleCore { Coord {1, 1}, '-', 250});
	food_obst_4.push_back( ParticleCore { Coord {2, 1}, '.', 250});
	food_obst_4.push_back( ParticleCore { Coord {3, 1}, '.', 250});
	food_obst_4.push_back( ParticleCore { Coord {4, 1}, '.', 250});
	food_obst_4.push_back( ParticleCore { Coord {5, 1}, '-', 250});
	food_obst_4.push_back( ParticleCore { Coord {6, 1}, '-', 250});
	food_obst_4.push_back( ParticleCore { Coord {7, 1}, '#', 52});
	food_obst_4.push_back( ParticleCore { Coord {8, 1}, '#', 52});
	food_obst_4.push_back( ParticleCore { Coord {9, 1}, '#', 52});
	food_obst_4.push_back( ParticleCore { Coord {10, 1}, '#', 52});
	food_obst_4.push_back( ParticleCore { Coord {11, 1}, '#', 52});
	food_obst_4.push_back( ParticleCore { Coord {12, 1}, '#', 52});
	OBJECT_VARS2.push_back(food_obst_4);

	/* mug of beer (same source as above) 
         .:.      .:.         .:.
       _oOoOo   _oOoOo       oOoOo_
      [_|||||  [_|||||       |||||_]
        |||||    |||||       |||||
        ~~~~~    ~~~~~       ~~~~~

	*/
    vector<ParticleCore> food_obst_5; 
	food_obst_5.push_back( ParticleCore { Coord {5, 7}, 0, 2});
	food_obst_5.push_back( ParticleCore { Coord {0, 1}, 'o', 15});
	food_obst_5.push_back( ParticleCore { Coord {0, 2}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {0, 3}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {0, 4}, '~', 15});
	food_obst_5.push_back( ParticleCore { Coord {1, 0}, '.', 15});
	food_obst_5.push_back( ParticleCore { Coord {1, 1}, 'O', 15});
	food_obst_5.push_back( ParticleCore { Coord {1, 2}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {1, 3}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {1, 4}, '~', 15});
	food_obst_5.push_back( ParticleCore { Coord {2, 0}, ':', 15});
	food_obst_5.push_back( ParticleCore { Coord {2, 1}, 'o', 15});
	food_obst_5.push_back( ParticleCore { Coord {2, 2}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {2, 3}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {2, 4}, '~', 15});
	food_obst_5.push_back( ParticleCore { Coord {3, 0}, '.', 15});
	food_obst_5.push_back( ParticleCore { Coord {3, 1}, 'O', 15});
	food_obst_5.push_back( ParticleCore { Coord {3, 2}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {3, 3}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {3, 4}, '~', 15});
	food_obst_5.push_back( ParticleCore { Coord {4, 1}, 'o', 15});
	food_obst_5.push_back( ParticleCore { Coord {4, 2}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {4, 3}, '|', 94});
	food_obst_5.push_back( ParticleCore { Coord {4, 4}, '~', 15});
	food_obst_5.push_back( ParticleCore { Coord {5, 1}, '_', 15});
	food_obst_5.push_back( ParticleCore { Coord {5, 2}, '_', 15});
	food_obst_5.push_back( ParticleCore { Coord {6, 2}, ']', 15});
	OBJECT_VARS2.push_back(food_obst_5);

	OBJ_THEMES.push_back(OBJECT_VARS2);


	/* SPORTS THEMES */
	/* baseball */
	vector<ParticleCore> sport_obst_1; 
	sport_obst_1.push_back( ParticleCore { Coord {3, 6}, 0, 1});
	sport_obst_1.push_back( ParticleCore { Coord {0, 0}, ',', 0});
	sport_obst_1.push_back( ParticleCore { Coord {0, 1}, '8', 0});
	sport_obst_1.push_back( ParticleCore { Coord {0, 2}, '\'', 0});
	sport_obst_1.push_back( ParticleCore { Coord {1, 0}, '\\', 88});
	sport_obst_1.push_back( ParticleCore { Coord {1, 2}, '/', 88});
	sport_obst_1.push_back( ParticleCore { Coord {2, 0}, ':', 0});
	sport_obst_1.push_back( ParticleCore { Coord {2, 1}, ')', 88});
	sport_obst_1.push_back( ParticleCore { Coord {2, 2}, ':', 0});
	sport_obst_1.push_back( ParticleCore { Coord {3, 0}, ':', 0});
	sport_obst_1.push_back( ParticleCore { Coord {3, 1}, '(', 88});
	sport_obst_1.push_back( ParticleCore { Coord {3, 2}, ':', 0});
	sport_obst_1.push_back( ParticleCore { Coord {4, 0}, '/', 88});
	sport_obst_1.push_back( ParticleCore { Coord {4, 2}, '\\', 88});
	sport_obst_1.push_back( ParticleCore { Coord {5, 0}, ',', 0});
	sport_obst_1.push_back( ParticleCore { Coord {5, 1}, '8', 0});
	sport_obst_1.push_back( ParticleCore { Coord {5, 2}, '\'', 0});
	OBJECT_VARS3.push_back(sport_obst_1);

	/* football */
	vector<ParticleCore> sport_obst_2; 
	sport_obst_2.push_back( ParticleCore { Coord {4, 9}, 0, 1});
	sport_obst_2.push_back( ParticleCore { Coord {0, 1}, '(', 130});
	sport_obst_2.push_back( ParticleCore { Coord {1, 0}, '.', 130});
	sport_obst_2.push_back( ParticleCore { Coord {1, 1}, '-', 130});
	sport_obst_2.push_back( ParticleCore { Coord {1, 2}, '`', 130});
	sport_obst_2.push_back( ParticleCore { Coord {2, 0}, '-', 130});
	sport_obst_2.push_back( ParticleCore { Coord {2, 1}, '<', 15});
	sport_obst_2.push_back( ParticleCore { Coord {2, 2}, '-', 130});
	sport_obst_2.push_back( ParticleCore { Coord {3, 0}, '~', 130});
	sport_obst_2.push_back( ParticleCore { Coord {3, 1}, '|', 15});
	sport_obst_2.push_back( ParticleCore { Coord {3, 2}, '.', 130});
	sport_obst_2.push_back( ParticleCore { Coord {4, 0}, '~', 130});
	sport_obst_2.push_back( ParticleCore { Coord {4, 1}, '|', 15});
	sport_obst_2.push_back( ParticleCore { Coord {4, 2}, '_', 130});
	sport_obst_2.push_back( ParticleCore { Coord {5, 0}, '~', 130});
	sport_obst_2.push_back( ParticleCore { Coord {5, 1}, '|', 15});
	sport_obst_2.push_back( ParticleCore { Coord {5, 2}, '.', 130});
	sport_obst_2.push_back( ParticleCore { Coord {6, 0}, '-', 130});
	sport_obst_2.push_back( ParticleCore { Coord {6, 1}, '>', 15});
	sport_obst_2.push_back( ParticleCore { Coord {6, 2}, '-', 130});
	sport_obst_2.push_back( ParticleCore { Coord {7, 0}, '.', 130});
	sport_obst_2.push_back( ParticleCore { Coord {7, 1}, '-', 130});
	sport_obst_2.push_back( ParticleCore { Coord {7, 2}, '\'', 130});
	sport_obst_2.push_back( ParticleCore { Coord {8, 1}, ')', 130});
	OBJECT_VARS3.push_back(sport_obst_2);

	/* dart - http://www.chris.com/ascii/joan/www.geocities.com/SoHo/7373/sports.html
	    ____                            ___ 
        \___\_.:::::::.___  ___.:::::._/__/
   jgs  /___/ ':::::::'        ':::::' \__\

	*/
   	vector<ParticleCore> sport_obst_3;  // !!!!! causes core dump
	sport_obst_3.push_back( ParticleCore { Coord {3, 15}, 0, 1});
	sport_obst_3.push_back( ParticleCore { Coord {0, 1}, '_', 15});
	sport_obst_3.push_back( ParticleCore { Coord {1, 1}, '_', 15});
	sport_obst_3.push_back( ParticleCore { Coord {2, 1}, '_', 15});
	sport_obst_3.push_back( ParticleCore { Coord {3, 1}, '.', 21});
	sport_obst_3.push_back( ParticleCore { Coord {4, 1}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {5, 1}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {6, 1}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {7, 1}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {8, 1}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {9, 1}, '.', 21});
	sport_obst_3.push_back( ParticleCore { Coord {10, 1}, '_', 15});
	sport_obst_3.push_back( ParticleCore { Coord {11, 1}, '/', 9});
	sport_obst_3.push_back( ParticleCore { Coord {12, 1}, '_', 9});
	sport_obst_3.push_back( ParticleCore { Coord {13, 1}, '_', 9});
	sport_obst_3.push_back( ParticleCore { Coord {14, 1}, '/', 9});
	sport_obst_3.push_back( ParticleCore { Coord {3, 2}, '\'', 21});
	sport_obst_3.push_back( ParticleCore { Coord {4, 2}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {5, 2}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {6, 2}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {7, 2}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {8, 2}, ':', 21});
	sport_obst_3.push_back( ParticleCore { Coord {9, 2}, '\'', 21});
	sport_obst_3.push_back( ParticleCore { Coord {11, 2}, '\\', 9});
	sport_obst_3.push_back( ParticleCore { Coord {12, 2}, '_', 9});
	sport_obst_3.push_back( ParticleCore { Coord {13, 2}, '_', 9});
	sport_obst_3.push_back( ParticleCore { Coord {14, 2}, '\\', 9});
	sport_obst_3.push_back( ParticleCore { Coord {12, 0}, '_', 9});
	sport_obst_3.push_back( ParticleCore { Coord {13, 0}, '_', 9});
	sport_obst_3.push_back( ParticleCore { Coord {14, 0}, '_', 9});
	OBJECT_VARS3.push_back(sport_obst_3);

	/* arrow - http://www.chris.com/ascii/joan/www.geocities.com/SoHo/7373/sports.html
		<--------<<<< jgs
	*/
	vector<ParticleCore> sport_obst_4; 
	sport_obst_4.push_back( ParticleCore { Coord {1, 8}, 0, 1});
	sport_obst_4.push_back( ParticleCore { Coord {0, 0}, '<', 250});
	sport_obst_4.push_back( ParticleCore { Coord {1, 0}, '-', 94});
	sport_obst_4.push_back( ParticleCore { Coord {2, 0}, '-', 94});
	sport_obst_4.push_back( ParticleCore { Coord {3, 0}, '-', 94});
	sport_obst_4.push_back( ParticleCore { Coord {4, 0}, '-', 94});
	sport_obst_4.push_back( ParticleCore { Coord {5, 0}, '<', 15});
	sport_obst_4.push_back( ParticleCore { Coord {6, 0}, '<', 34});
	sport_obst_4.push_back( ParticleCore { Coord {7, 0}, '<', 15});
	OBJECT_VARS3.push_back(sport_obst_4);


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
