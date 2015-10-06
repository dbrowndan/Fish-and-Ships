// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 planet.h v1.0

#ifndef _BOAT_H               // Prevent multiple definitions if this 
#define _BOAT_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace boatNS
{
    const int   WIDTH = 512;                // image width
    const int   HEIGHT = 512;               // image height
    const int   COLLISION_RADIUS = 200/2;   // for circular collision
    const int   X = GAME_WIDTH/2 - WIDTH/2; // location on screen
    const int   Y = 0;
    const float MASS = 1.0e14f;         // mass
	const float SPEED = 200;			// speed
    const int   TEXTURE_COLS = 2;       // texture has 2 columns
    const int   START_FRAME = 1;        // starts at frame 1
    const int   END_FRAME = 1;          // no animation
}

class Boat : public Entity            // inherits from Entity class
{
public:
    // constructor
    Boat();
	void update(float frameTime);
private:
	bool rotationDir;
};
#endif