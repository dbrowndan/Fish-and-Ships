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
    radius          = fishNS::COLLISION_RADIUS;
    mass            = fishNS::MASS;
    startFrame      = fishNS::START_FRAME;    // first frame of ship animation
    endFrame        = fishNS::END_FRAME;      // last frame of ship animation
    setCurrentFrame(startFrame);
}