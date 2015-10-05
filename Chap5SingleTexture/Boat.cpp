// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "boat.h"

//=============================================================================
// default constructor
//=============================================================================
Boat::Boat() : Entity()
{
    spriteData.x    = boatNS::X;              // location on screen
    spriteData.y    = boatNS::Y;
    radius          = boatNS::COLLISION_RADIUS;
    mass            = boatNS::MASS;
    startFrame      = boatNS::START_FRAME;    // first frame of ship animation
    endFrame        = boatNS::END_FRAME;      // last frame of ship animation
    setCurrentFrame(startFrame);
}