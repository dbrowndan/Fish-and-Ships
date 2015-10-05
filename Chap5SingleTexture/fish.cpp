// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "fish.h"

//=============================================================================
// default constructor
//=============================================================================
Fish::Fish() : Entity()
{
    spriteData.x    = fishNS::X;              // location on screen
    spriteData.y    = fishNS::Y;
	spriteData.width = fishNS::WIDTH;           // size of boat1
    spriteData.height = fishNS::HEIGHT;
    radius          = fishNS::COLLISION_RADIUS;
    mass            = fishNS::MASS;
    velocity.x = 0;                           // velocity X 
	velocity.y = 0; 

}

void Fish::update(float frameTime){




}