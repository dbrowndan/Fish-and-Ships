// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar() {
	fishSpawnCount = 0;
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	if (!bkgTexture.initialize(graphics, BKG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!bkg.initialize(graphics, 0,0,0, &bkgTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	bkg.setX(0);
	bkg.setY(0);
	bkg.setScale(BKG_IMAGE_SCALE);

	if (!boatTexture.initialize(graphics, BOAT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Boat texture initialization failed"));
	if (!boat.initialize(graphics, 0,0,0, &boatTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init boat"));
	boat.setX(GAME_WIDTH/2 - boatTexture.getWidth()*BOAT_IMAGE_SCALE/2);
	boat.setY(0);
	boat.setScale(BOAT_IMAGE_SCALE);

	for (int i = 0; i < FISH_COUNT; i++) {
		if (!fishTexture[i].initialize(graphics, FISH_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Fish texture initialization failed"));
		if (!fish[i].initialize(graphics, 0,0,0, &fishTexture[i]))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error init fish"));
		fish[i].setScale(FISH_IMAGE_SCALE);

		fishPos[i].xPos = fish[i].getX();
		fishPos[i].yPos = fish[i].getY();
		fishVel[i].xVel = 0;
		fishVel[i].yVel = 0;
	}

	//Stuff for physics
	boatPos.xPos = boat.getX();
	boatPos.yPos = boat.getY();
	
	boatVel.xVel = 200;


    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	// arrow keys move boat
	if (input->isKeyDown(VK_LEFT)) boatPos.xPos = boat.getX() - boatVel.xVel*frameTime;
	if (input->isKeyDown(VK_RIGHT)) boatPos.xPos = boat.getX() + boatVel.xVel*frameTime;
	
	// don't let the boat go off the screen
	if (boatPos.xPos < 0) boatPos.xPos = 0;
	if (boatPos.xPos + boatTexture.getWidth()*BOAT_IMAGE_SCALE > GAME_WIDTH) boatPos.xPos = GAME_WIDTH - boatTexture.getWidth()*BOAT_IMAGE_SCALE;

	boat.setX(boatPos.xPos);

	// randomly spawn fish
	if (rand() % 300 == 0 && fishSpawnCount < FISH_COUNT) {
		fishPos[fishSpawnCount].xPos = rand() % (GAME_WIDTH - fish[fishSpawnCount].getWidth());
		fish[fishSpawnCount].setX(fishPos[fishSpawnCount].xPos);
		fishPos[fishSpawnCount].yPos = GAME_HEIGHT - 100;
		fish[fishSpawnCount].setY(fishPos[fishSpawnCount].yPos);
		fishVel[fishSpawnCount].xVel = 100;
		fishVel[fishSpawnCount].yVel = 100;
		fishSpawnCount++;
	}


	for (int i = 0; i < fishSpawnCount; i++) {
		int moveDistance = (boatPos.yPos + boat.getHeight() - fishPos[i].yPos) * 10;
		if (moveDistance < -10) fishPos[i].yPos += moveDistance * frameTime;
		else fishPos[i].yPos -= 10 * frameTime;
		fish[i].setY(fishPos[i].yPos);
		fishPos[i].xPos += (boatPos.xPos + boat.getWidth()/2 - (fishPos[i].xPos + fish[i].getWidth()/2)) * frameTime / 10;
		fish[i].setX(fishPos[i].xPos);
	}

 ////////////////
// INPUT MODS
 ////////////////

 int directionX = 0;
 int directionY = 0;

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	bkg.draw();
	boat.draw();
	// fish.draw();
	for (int i = 0; i < fishSpawnCount; i++){
		fish[i].draw();
	}

	

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	bkgTexture.onLostDevice();
	boatTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
   
	bkgTexture.onResetDevice();
	boatTexture.onResetDevice();

    Game::resetAll();
    return;
}
