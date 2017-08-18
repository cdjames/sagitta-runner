/********************************************************************
Author: Collin James
** Date: 7/9/17
** Description: Supporting data structures used for infinite runner 
*********************************************************************/

#ifndef SAGITTATYPES_HPP
#define SAGITTATYPES_HPP

#include <string>

#define DEF_TIMEOUT 20
#define DEF_BUFFER 10
#define BLANK ' '
#define KEY_SPACE 32
#define STATUS_SIZE 2
#define STAT_ENEMIES 18
#define STAT_BULLETS 16
#define STAT_SCORE 17
#define STAT_PLAYER 6
#define STAT_PL_MSG_OFFSET 4
#define QUAD_PARTS 3
#define MAX_BULLETS 5
#define MIN_BULLETS 1
#define MAX_OBSTACLES 100
#define MAX_EXPLOSIONS 25
#define DEF_THM_COUNTER 20
#define DIFF_TIMEOUT 5 // seconds
#define DIFF_TIME_ADD 2 // seconds
#define OBS_CREATE_FACTOR 5
#define MAX_OBS_POINTS 30
#define MAX_Y 24
#define MAX_X 80
#define GM_GAMEOVER -2
#define HS_COLOR 2
#define ALT_COLOR 7
#define QUIT_COLOR 7
#define STAT_COLOR 6
#define GO_COLOR 1
#define PN_COLOR 5
// #define DEBUG 1 // comment out to turn off debug comments
// #define TIMING 1 // comment out to turn off timing comments

#define DEF_PORT 30123
#define DEF_IP "127.0.0.1"


/* some enumerations of types that will be used throughout the game */
enum ObjectType { SHIP = 0, BULLET, EXPLOSION, OBSTACLE, NONE };
enum CollisionType { FRIENDLY = NONE + 1, GAMEOVER, HIT, NOHIT, EDGE, DESTROY, ALIVE };
enum ThemeType { SPACE = 0, FOOD, SPORTS, COMPUTERS};

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
} Coord;

typedef struct IPParams {
	std::string ip;
	int port;
} IPParams;

typedef struct CommStruct {
	char cmd[5];
	int move;
	int player;
	struct Coord shipCoord;
	int score;
	int difficulty;
	int numPlayers;
} CommStruct;

/* info about particle used in the main gameboard, and also in Particles themselves */
typedef struct ParticleInfo {
	ObjectType type;
	unsigned long id;
} ParticleInfo;

typedef struct ParticleCore {
	Coord coords;
	char symbol;
	unsigned int color; // to be used with ncurses color pairs
} ParticleCore;

/* forms the building blocks of objects like ships, bullets, obstacles, and explosions */
typedef struct Particle {
	ParticleCore core;
	ParticleInfo info;
	CollisionType collided;
} Particle;


#define NUM_TYPES OBSTACLE+1
#define NUM_THEMES SPORTS+1 
#define DUMMY_PARTICLE Particle { ParticleCore { Coord {-99, -99}, BLANK, 0 }, ParticleInfo { NONE, 0}, NOHIT }; // color 7 is white

#endif
