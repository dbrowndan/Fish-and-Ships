// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "fish.h"
#include "math.h"

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
	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;
}

void Fish::setTowards(Entity &boat) {
	
	// Set vel towards boat
	velocity.x = boat.getX() + rand() % boat.getWidth() * BOAT_IMAGE_SCALE - getCenterX();
	velocity.y = boat.getY() + boat.getHeight() * BOAT_IMAGE_SCALE - spriteData.y;

	D3DXVec2Normalize(&velocity, &velocity);

	velocity *= fishNS::SPEED;

	// Set texture to face boat
	if(!spriteData.flipHorizontal && spriteData.x > boat.getCenterX()) spriteData.flipHorizontal = true;
	if(spriteData.flipHorizontal && spriteData.x + getWidth() < boat.getCenterX()) spriteData.flipHorizontal = false;

	// Set angle towards boat
	if(spriteData.flipHorizontal) setRadians(atan(spriteData.y / spriteData.x));
	else setRadians(-atan(spriteData.y / spriteData.x));

}