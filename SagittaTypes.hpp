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
enum CollisionType { FRIENDLY = OBSTACLE + 1, GAMEOVER, HIT, NOHIT };
enum ThemeType { SPORTS = HIT + 1, FOOD, SPACE };

/* simple coordinate structure */
typedef struct Coord {
	int x;
	int y;
} Coord;

/* info about particle used in the main gameboard, and also in Particles themselves */
typedef struct ParticleInfo {
	ObjectType type;
	unsigned long id;
} ParticleInfo;

/* forms the building blocks of objects like ships, bullets, obstacles, and explosions */
typedef struct Particle {
	Coord coords;
	char symbol;
	unsigned int color; // to be used with ncurses color pairs
	ParticleInfo info;
	CollisionType collided;
} Particle;



#endif