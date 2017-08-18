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
	vector< vector<ParticleCore> > OBJECT_VARS_COMP;

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

	OBJECT_VARS_COMP.push_back(DEF_SHIP_BP);
	OBJ_THEMES.push_back(OBJECT_VARS_COMP);
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
	vector< vector<ParticleCore> > OBJECT_VARS_COMP;

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

	vector<ParticleCore> comp_bullet_1;
	comp_bullet_1.push_back( ParticleCore { Coord {1, 1} , 0, 0} ); // first line is the height and width
	comp_bullet_1.push_back( ParticleCore { Coord {0, 0}, '#', 196} ); // then x, y, symbol, color
	OBJECT_VARS_COMP.push_back(comp_bullet_1);
	OBJ_THEMES.push_back(OBJECT_VARS_COMP);

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);

}

void createExplosionBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES;
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;
	vector< vector<ParticleCore> > OBJECT_VARS_COMP;

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

	OBJECT_VARS_COMP.push_back(DEF_EXP_BP);
	OBJECT_VARS_COMP.push_back(exp_2);
	OBJ_THEMES.push_back(OBJECT_VARS_COMP);

	/* Finally, append to the master blueprint */
	OBJ_BLPRNTS.push_back(OBJ_THEMES);

}

void createObstacleBlueprints() {
	vector< vector< vector<ParticleCore> > > OBJ_THEMES;
	vector< vector<ParticleCore> > OBJECT_VARS;
	vector< vector<ParticleCore> > OBJECT_VARS2;
	vector< vector<ParticleCore> > OBJECT_VARS3;
	vector< vector<ParticleCore> > OBJECT_VARS_COMP;

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


	/*
            .--
         __(__
       /`  |  `\
       |___O___|
       |       |
       |       |
   jgs  '.___.'
   http://www.chris.com/ascii/joan/www.geocities.com/SoHo/7373/computer.html
	*/

	vector<ParticleCore> comp_obst_mouse; 
	comp_obst_mouse.push_back( ParticleCore { Coord {9, 7}, 0, 2});
	comp_obst_mouse.push_back( ParticleCore { Coord {0, 2}, '/', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {0, 3}, '|', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {0, 4}, '|', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {0, 5}, '|', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {1, 2}, '`', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {1, 3}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {1, 6}, '\'', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {2, 1}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {2, 3}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {2, 6}, '.', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {3, 1}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {3, 3}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {3, 6}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {4, 1}, '(', 239});
	comp_obst_mouse.push_back( ParticleCore { Coord {4, 2}, '|', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {4, 3}, 'O', 242});
	comp_obst_mouse.push_back( ParticleCore { Coord {4, 6}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {5, 0}, '.', 239});
	comp_obst_mouse.push_back( ParticleCore { Coord {5, 1}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {5, 3}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {5, 6}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {6, 0}, '-', 239});
	comp_obst_mouse.push_back( ParticleCore { Coord {6, 1}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {6, 3}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {6, 6}, '.', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {7, 0}, '-', 239});
	comp_obst_mouse.push_back( ParticleCore { Coord {7, 2}, '`', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {7, 3}, '_', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {7, 6}, '\'', 180});
	// comp_obst_mouse.push_back( ParticleCore { Coord {8, 0}, '\'', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {8, 2}, '\\', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {8, 3}, '|', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {8, 4}, '|', 180});
	comp_obst_mouse.push_back( ParticleCore { Coord {8, 5}, '|', 180});
	OBJECT_VARS_COMP.push_back(comp_obst_mouse);

	/* 			http://www.chris.com/ascii/joan/www.geocities.com/SoHo/7373/computer.html      
       _______
     .`   |__|`.
     |         |
     | .-----. | 
     | |stuff| |
 jgs |_:_____:_|
	*/

 	vector<ParticleCore> comp_obst_floppy; 
	comp_obst_floppy.push_back( ParticleCore { Coord {11, 6}, 0, 1});
	comp_obst_floppy.push_back( ParticleCore { Coord {0, 1}, '.', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {0, 2}, '|', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {0, 3}, '|', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {0, 4}, '|', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {0, 5}, '|', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {1, 1}, '`', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {1, 5}, '_', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {2, 0}, '_', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {2, 3}, '.', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {2, 4}, '|', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {2, 5}, ':', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {3, 0}, '_', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {3, 3}, '-', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {3, 4}, 's', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {3, 5}, '_', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {4, 0}, '_', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {4, 3}, '-', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {4, 4}, 't', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {4, 5}, '_', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {5, 0}, '_', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {5, 1}, '|', 240});
	comp_obst_floppy.push_back( ParticleCore { Coord {5, 3}, '-', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {5, 4}, 'u', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {5, 5}, '_', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {6, 0}, '_', 240});
	comp_obst_floppy.push_back( ParticleCore { Coord {6, 1}, '_', 240});
	comp_obst_floppy.push_back( ParticleCore { Coord {6, 3}, '-', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {6, 4}, 'f', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {6, 5}, '_', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {7, 0}, '_', 240});
	comp_obst_floppy.push_back( ParticleCore { Coord {7, 1}, '_', 240});
	comp_obst_floppy.push_back( ParticleCore { Coord {7, 3}, '-', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {7, 4}, 'f', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {7, 5}, '_', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {8, 0}, '_', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {8, 1}, '|', 240});
	comp_obst_floppy.push_back( ParticleCore { Coord {8, 3}, '.', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {8, 4}, '|', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {8, 5}, ':', 15});
	comp_obst_floppy.push_back( ParticleCore { Coord {9, 1}, '`', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {9, 5}, '_', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {10, 1}, '.', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {10, 2}, '|', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {10, 3}, '|', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {10, 4}, '|', 130});
	comp_obst_floppy.push_back( ParticleCore { Coord {10, 5}, '|', 130});
	OBJECT_VARS_COMP.push_back(comp_obst_floppy);


/* little mouse
    _
     )
    /T\
    \_/
*/
    vector<ParticleCore> comp_obst_lil_mouse; 
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {3, 4}, 0, 2});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {0, 0}, '_', 239});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {1, 1}, ')', 239});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {0, 2}, '/', 33});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {1, 2}, 'T', 39});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {2, 2}, '\\', 33});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {0, 3}, '\\', 33});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {1, 3}, '_', 33});
	comp_obst_lil_mouse.push_back( ParticleCore { Coord {2, 3}, '/', 33});
	OBJECT_VARS_COMP.push_back(comp_obst_lil_mouse);

	OBJ_THEMES.push_back(OBJECT_VARS_COMP);
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
