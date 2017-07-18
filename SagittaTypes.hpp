/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Supporting data structures used for infinite runner 
*********************************************************************/

#ifndef SAGITTATYPES_HPP
#define SAGITTATYPES_HPP

#define DEF_TIMEOUT 20
#define DEF_BUFFER 10
#define BLANK ' '

/* some enumerations of types that will be used throughout the game */
enum ObjectType { SHIP = 0, BULLET, OBSTACLE, NONE };
enum CollisionType { FRIENDLY = NONE + 1, GAMEOVER, HIT, NOHIT, EDGE };
enum ThemeType { SPACE = 0, FOOD, SPORTS };

/* simple coordinate structure */
typedef struct Coord {
	int x;
	int y;
	Coord& operator+=(const Coord& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Coord& operator=(const Coord& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
} Coord;

/* info about particle used in the main gameboard, and also in Particles themselves */
typedef struct ParticleInfo {
	ObjectType type;
	unsigned long id;
	ParticleInfo& operator=(const ParticleInfo rhs) {
		type = rhs.type;
		id = rhs.id;
		return *this;
	}
} ParticleInfo;

typedef struct ParticleCore {
	Coord coords;
	char symbol;
	unsigned int color; // to be used with ncurses color pairs
	ParticleCore& operator=(const ParticleCore rhs) {
		coords = rhs.coords;
		symbol = rhs.symbol;
		color = rhs.color;
		return *this;
	}
} ParticleCore;

/* forms the building blocks of objects like ships, bullets, obstacles, and explosions */
typedef struct Particle {
	// Coord coords;
	// char symbol;
	// unsigned int color; // to be used with ncurses color pairs
	ParticleCore core;
	ParticleInfo info;
	CollisionType collided;

	Particle& operator=(const Particle rhs) {
		core = rhs.core;
		info = rhs.info;
		collided = rhs.collided;
		return *this;
	}
} Particle;


#define NUM_TYPES OBSTACLE+1
#define NUM_THEMES SPORTS+1 
#define DUMMY_PARTICLE Particle { ParticleCore { Coord {-99, -99}, BLANK, 0 }, NONE, NOHIT }; // color 7 is white

#endif