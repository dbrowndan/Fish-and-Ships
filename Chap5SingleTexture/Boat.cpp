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
	spriteData.width = boatNS::WIDTH;           // size of boat1
    spriteData.height = boatNS::HEIGHT;
    spriteData.x = boatNS::X;                   // location on screen
    spriteData.y = boatNS::Y;
    spriteData.rect.bottom = boatNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = boatNS::WIDTH;
	velocity.x = 0;                           // velocity X 
	velocity.y = 0; 
    radius = boatNS::COLLISION_RADIUS;
	rotationDir = true; // counterclockwise
	
}

 void Boat::update(float frameTime){
	Entity::update(frameTime);
	// arrow keys to move boat
	if (input->isKeyDown(VK_LEFT)) velocity.x = -boatNS::SPEED;
	else if (input->isKeyDown(VK_RIGHT)) velocity.x = boatNS::SPEED;
	else velocity.x = 0;

	spriteData.x +=  velocity.x * frameTime;

	// don't let the boat go off the screen
	if (spriteData.x < 0) spriteData.x = 0;
	if (spriteData.x + spriteData.width * BOAT_IMAGE_SCALE > GAME_WIDTH) spriteData.x = GAME_WIDTH - spriteData.width * BOAT_IMAGE_SCALE;

	if (getRadians() > PI / 64) rotationDir = false;
	if (getRadians() < -PI / 64) rotationDir = true;
	if (rotationDir) setRadians(getRadians() + (PI / 64 * frameTime));
	else setRadians(getRadians() - (PI / 64 * frameTime));
 }
