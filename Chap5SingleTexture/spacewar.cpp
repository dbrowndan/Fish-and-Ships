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
	boomCounter = 0;
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

	if (!boomTexture.initialize(graphics, BOOM_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!healthTexture.initialize(graphics, HEALTH_IMAGE))
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
		fish[i].setX(GAME_WIDTH * 4);
		fish[i].setY(GAME_HEIGHT * 4);
		int randomSpeed = rand() % 100;
		if(randomSpeed < 33) fish[i].setSpeed(FISH_SPEED_SLOW); // VECTOR2(X, Y)
		else if(randomSpeed < 66) fish[i].setSpeed(FISH_SPEED_MEDIUM);
		else fish[i].setSpeed(FISH_SPEED_FAST);
		fish[i].setVelocity(VECTOR2(fish[i].getSpeed(), -fish[i].getSpeed()));
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

	//booms
	for (int i = 0; i < FISH_COUNT; i++) {
		if (!booms[i].initialize(this, 0, 0, 0, &boomTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Boom texture initialization failed"));
		booms[i].setX(GAME_WIDTH * 3);
		booms[i].setY(GAME_HEIGHT * 3);
		booms[i].setScale(BOOM_IMAGE_SCALE);
	}

	//health
	for (int i = 0; i < HEALTH_COUNT; i++) {
		if (!health[i].initialize(graphics, 0, 0, 0, &healthTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Health texture initialization failed"));
		health[i].setX(GAME_WIDTH - (HEALTH_COUNT - i) * health[i].getWidth() * HEALTH_IMAGE_SCALE - 10);
		health[i].setY(10);
		health[i].setScale(HEALTH_IMAGE_SCALE);
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
			bombs[idleBombs].setActive(true);
			bombs[idleBombs].setVisible(true);
		}
		input->clearKeyPress(VK_SPACE);
	}

	for (int i = 0; i < BOMB_COUNT; i++) {
		bombs[i].update(frameTime);
	}

	//spawn fish
	if (rand() % 100 == 0 && fishSpawnCount < FISH_COUNT) {
		fish[fishSpawnCount].setActive(true);
		fish[fishSpawnCount].setX(rand() % GAME_WIDTH);
		fish[fishSpawnCount].setY(GAME_HEIGHT);

		// flip fish to face boat
		if (fish[fishSpawnCount].getX() + fish[fishSpawnCount].getWidth() * FISH_IMAGE_SCALE / 2
			> boat.getX() + boat.getWidth() * BOAT_IMAGE_SCALE / 2) {
				fish[fishSpawnCount].flipHorizontal(true);
		}

		fishSpawnCount++;
	}

	boat.update(frameTime);

	for (int i = 0; i < fishSpawnCount; i++) {
		fish[i].setTowards(boat);
		fish[i].update(frameTime);
	}

	for (int i = 0; i < FISH_COUNT; i++){
		if (booms[i].getActive()){
			booms[i].timeOnScreen += frameTime;
			if (booms[i].timeOnScreen > 1){
				booms[i].setActive(false);
				booms[i].setVisible(false);
				booms[i].timeOnScreen = 0;
			}
		}
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

	for (int i = 0; i < BOMB_COUNT; i++){
		for (int j = 0; j < FISH_COUNT; j++){
			if(bombs[i].collidesWith(fish[j], collisionVector)){
				booms[boomCounter].setX(bombs[i].getCenterX() - booms[i].getWidth() * BOOM_IMAGE_SCALE / 2);
				booms[boomCounter].setY(bombs[i].getY());
				booms[boomCounter].setActive(true);
				booms[boomCounter].setVisible(true);
				boomCounter++;
				if(boomCounter > FISH_COUNT) boomCounter = 0;
				bombs[i].setX(GAME_WIDTH * 2);
				bombs[i].setY(GAME_HEIGHT * 2);
				fish[j].setActive(false);
				fish[j].setVisible(false);
			}
		}
	}

	// fish attack boat
	for (int i = 0; i < FISH_COUNT; i++){
		if(fish[i].collidesWith(boat, collisionVector)){
			if(fish[i].getTimeSinceAttack() >= FISH_ATTACK_TIME) {
				boat.setHealth(boat.getHealth() - 1);
				if(boat.getHealth() == 0) lose();
				fish[i].setTimeSinceAttack(0);
			}
			else fish[i].setTimeSinceAttack(fish[i].getTimeSinceAttack() + frameTime);
		}
	}


}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites
	
	if(boat.getHealth() > 0) {
		bkg.draw();
		boat.draw();
		for (int i = 0; i < FISH_COUNT; i++) fish[i].draw();
		for (int i = 0; i < BOMB_COUNT; i++) bombs[i].draw();
		for (int i = 0; i < FISH_COUNT; i++) booms[i].draw();
		for (int i = 0; i < boat.getHealth(); i++) health[i].draw();
	}
	else gameOver.draw();

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
	fishTexture.onLostDevice();
	bombTexture.onLostDevice();
	boomTexture.onLostDevice();
	healthTexture.onLostDevice();
	gameOverTexture.onLostDevice();

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
	fishTexture.onResetDevice();
	bombTexture.onResetDevice();
	boomTexture.onResetDevice();
	healthTexture.onResetDevice();
	gameOverTexture.onResetDevice();

    Game::resetAll();
    return;
}

int Spacewar::nextIdleBomb()
{
	for (int i = 0; i < BOMB_COUNT; i++){
		if (!bombs[i].getActive()){
			return i;
		}
	}

	return -1;
}

void Spacewar::lose() {
	if (!gameOverTexture.initialize(graphics, GAME_OVER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Game over texture initialization failed"));
	if (!gameOver.initialize(graphics, 0,0,0, &gameOverTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init game over"));
	gameOver.setX(0);
	gameOver.setY(0);
	gameOver.setScale(GAME_OVER_IMAGE_SCALE);
}