// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include "time.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar() {
	fishSpawnCount = 0;
	bombsOnScreen = 0;
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

	srand(time(NULL));

	if (!bkgTexture.initialize(graphics, BKG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Bkg texture initialization failed"));
	if (!bkg.initialize(graphics, 0,0,0, &bkgTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));
	bkg.setX(0);
	bkg.setY(0);
	bkg.setScale(BKG_IMAGE_SCALE);

	if (!boatTexture.initialize(graphics, BOAT_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!fishTexture.initialize(graphics, FISH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!bombTexture.initialize(graphics, BOMB_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

 // boat
	if (!boat.initialize(this, 0, 0, 0, &boatTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boat"));
    boat.setX(GAME_WIDTH/2 - boatTexture.getWidth()*BOAT_IMAGE_SCALE/2);
	boat.setY(0);
    boat.setVelocity(VECTOR2(boatNS::SPEED,-boatNS::SPEED)); // VECTOR2(X, Y)
	boat.setScale(BOAT_IMAGE_SCALE);
	boat.setVelocity(VECTOR2(boatNS::SPEED,0)); // VECTOR2(X, Y)

	// fish
	for (int i = 0; i < FISH_COUNT; i++) {
		if (!fish[i].initialize(this, 0, 0, 0, &fishTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Fish texture initialization failed"));
		fish[i].setX(GAME_WIDTH * 2);
		fish[i].setY(GAME_HEIGHT * 2);
		fish[i].setVelocity(VECTOR2(fishNS::SPEED,-fishNS::SPEED)); // VECTOR2(X, Y)
		fish[i].setScale(FISH_IMAGE_SCALE);
	}

	//bombs
	for (int i = 0; i < BOMB_COUNT; i++) {
		if (!bombs[i].initialize(this, 0, 0, 0, &bombTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Fish texture initialization failed"));
		bombs[i].setX(GAME_WIDTH * 2);
		bombs[i].setY(GAME_HEIGHT * 2);
		bombs[i].setVelocity(VECTOR2(0,bombNS::SPEED)); // VECTOR2(X, Y)
		bombs[i].setScale(BOMB_IMAGE_SCALE);
	}

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	// create bomb on space click
	if (input->wasKeyPressed(VK_SPACE)){
		int idleBombs = nextIdleBomb();
		if (idleBombs != -1){
			bombs[idleBombs].setX(boat.getCenterX() - (bombs[idleBombs].getWidth() * BOMB_IMAGE_SCALE) / 2);
			bombs[idleBombs].setY(boat.getY() + boat.getHeight() * BOAT_IMAGE_SCALE);
			bombs[idleBombs].isOnScreen = true;
		}
		input->clearKeyPress(VK_SPACE);
	}

	for (int i = 0; i < BOMB_COUNT; i++) {
		bombs[i].update(frameTime);
	}
	//spawn fish
	if (rand() % 1000 == 0 && fishSpawnCount < FISH_COUNT) {
		fish[fishSpawnCount].setX(rand() % GAME_WIDTH);
		if (fish[fishSpawnCount].getX() + fish[fishSpawnCount].getWidth() * FISH_IMAGE_SCALE / 2
			> boat.getX() + boat.getWidth() * BOAT_IMAGE_SCALE / 2) {
				fish[fishSpawnCount].flipHorizontal(true);
		}

		fish[fishSpawnCount].setY(GAME_HEIGHT);
		fishSpawnCount++;
	}

	boat.update(frameTime);

	for (int i = 0; i < fishSpawnCount; i++) {
		fish[i].setTowards(boat);
		fish[i].update(frameTime);
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
{
	VECTOR2 collisionVector;


}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	bkg.draw();
	boat.draw();
	for (int i = 0; i < FISH_COUNT; i++) fish[i].draw();
	for (int i = 0; i < BOMB_COUNT; i++) bombs[i].draw();

	

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

int Spacewar::nextIdleBomb()
{
	for (int i = 0; i < BOMB_COUNT; i++){
		if (!bombs[i].isOnScreen){
			return i;
		}
	}

	return -1;
}