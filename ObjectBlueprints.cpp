#include "ObjectBlueprints.hpp"

void createShipBlueprint() {
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
}

vector<ParticleCore> DEF_SHIP_BP; // (11, ParticleCore {0, 0, 0, 0});
// addToVector(def_ship_bp, ParticleCore {3, 5, NULL, NULL} ); // first line is the height and width
// def_ship_bp.push_back( ParticleCore {3, 5, NULL, NULL} ); // first line is the height and width
// def_ship_bp.push_back( ParticleCore {1, 0, '\\', 1} ); // then x, y, symbol, color
// def_ship_bp.push_back( ParticleCore {2, 0, '\\', 1} );
// def_ship_bp.push_back( ParticleCore {0, 1, '}', 7} );
// def_ship_bp.push_back( ParticleCore {1, 1, '=', 7} );
// def_ship_bp.push_back( ParticleCore {2, 1, 'x', 1} );
// def_ship_bp.push_back( ParticleCore {3, 1, '=', 7} );
// def_ship_bp.push_back( ParticleCore {4, 1, '>', 7} );
// def_ship_bp.push_back( ParticleCore {1, 2, '/', 1} );
// def_ship_bp.push_back( ParticleCore {2, 2, '/', 1} );

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
