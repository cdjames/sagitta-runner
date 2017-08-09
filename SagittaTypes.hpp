/*********************************************************************
** Author: Collin James
** Date: 7/9/17
** Description: Supporting data structures used for infinite runner 
*********************************************************************/

#ifndef SAGITTATYPES_HPP
#define SAGITTATYPES_HPP

#include <mutex>

#define DEF_TIMEOUT 20
#define DEF_BUFFER 10
#define BLANK ' '
#define KEY_SPACE 32
#define STATUS_SIZE 2
#define STAT_ENEMIES 18
#define STAT_BULLETS 16
#define STAT_SCORE 17
#define STAT_PLAYER 6
#define QUAD_PARTS 3
#define MAX_BULLETS 5
#define MIN_BULLETS 1
#define MAX_OBSTACLES 100
#define MAX_EXPLOSIONS 25
#define DEF_THM_COUNTER 20
#define DIFF_TIMEOUT 5 // seconds
#define DIFF_TIME_ADD 2 // seconds
#define OBS_CREATE_FACTOR 5
#define MAX_OBS_POINTS 20
#define MAX_Y 24
#define MAX_X 80


/* some enumerations of types that will be used throughout the game */
enum ObjectType { SHIP = 0, BULLET, EXPLOSION, OBSTACLE, NONE };
enum CollisionType { FRIENDLY = NONE + 1, GAMEOVER, HIT, NOHIT, EDGE, DESTROY, ALIVE };
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
	Coord& operator-=(const Coord& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	friend Coord operator+(const Coord& rhs, const Coord& lhs) {
		Coord res = rhs;
		res += lhs;
		return res;
	}
	friend Coord operator-(const Coord& rhs, const Coord& lhs) {
		Coord res = rhs;
		res -= lhs;
		return res;
	}

	// Coord& operator=(const Coord& rhs) {
	// 	x = rhs.x;
	// 	y = rhs.y;
	// 	return *this;
	// }
} Coord;

// Coord operator+(const Coord& right, const Coord& left) {
// 	Coord res = right;
// 	res += left;
// 	return res;
// }

/* info about particle used in the main gameboard, and also in Particles themselves */
typedef struct ParticleInfo {
	ObjectType type;
	unsigned long id;
	// ParticleInfo& operator=(const ParticleInfo rhs) {
	// 	type = rhs.type;
	// 	id = rhs.id;
	// 	return *this;
	// }
} ParticleInfo;

typedef struct ParticleCore {
	Coord coords;
	char symbol;
	unsigned int color; // to be used with ncurses color pairs
	// ParticleCore& operator=(const ParticleCore rhs) {
	// 	coords = rhs.coords;
	// 	symbol = rhs.symbol;
	// 	color = rhs.color;
	// 	return *this;
	// }
} ParticleCore;

/* forms the building blocks of objects like ships, bullets, obstacles, and explosions */
typedef struct Particle {
	// Coord coords;
	// char symbol;
	// unsigned int color; // to be used with ncurses color pairs
	ParticleCore core;
	ParticleInfo info;
	CollisionType collided;

	// Particle& operator=(const Particle rhs) {
	// 	core = rhs.core;
	// 	info = rhs.info;
	// 	collided = rhs.collided;
	// 	return *this;
	// }
} Particle;


#define NUM_TYPES OBSTACLE+1
#define NUM_THEMES SPORTS+1 
#define DUMMY_PARTICLE Particle { ParticleCore { Coord {-99, -99}, BLANK, 0 }, ParticleInfo { NONE, 0}, NOHIT }; // color 7 is white

#endif