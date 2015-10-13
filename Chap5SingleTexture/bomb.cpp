// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "bomb.h"
#include "math.h"

//=============================================================================
// default constructor
//=============================================================================
Bomb::Bomb() : Entity()
{
    spriteData.x    = bombNS::X;              // location on screen
    spriteData.y    = bombNS::Y;
	spriteData.width = bombNS::WIDTH;           // size of boat1
    spriteData.height = bombNS::HEIGHT;
	spriteData.rect.bottom = bombNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = bombNS::WIDTH;
    radius          = bombNS::COLLISION_RADIUS;
    mass            = bombNS::MASS;
    velocity.x = 0;                           // velocity X 
	velocity.y = 0;
	active = false;
}

void Bomb::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.y += velocity.y * frameTime;

}