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
	dxFontMedium	= new TextDX();
	fishSpawnCount = 0;
	bombsOnScreen = 0;
	reloadTime = 0;
	boomCounter = 0;
	displayMenu = true;
	spawnRate = 0;
	boomCounter_2 = 0;
	score = 0;
	winBool = false;
	fishDead = 0;
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

	audio->playCue(BKG_MUSIC);

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

	if (!boatTexture_75.initialize(graphics, BOAT_IMAGE_75))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!boatTexture_50.initialize(graphics, BOAT_IMAGE_50))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!boatTexture_25.initialize(graphics, BOAT_IMAGE_25))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!fishTexture.initialize(graphics, FISH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!bombTexture.initialize(graphics, BOMB_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!boomTexture.initialize(graphics, BOOM_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!boomTexture_2.initialize(graphics, BOOM_IMAGE_2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!healthTexture.initialize(graphics, HEALTH_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	if (!menuTexture.initialize(graphics, MENU_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));
	if (!menu.initialize(graphics, 0,0,0, &menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init bkg"));

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

	//booms 2
	for (int i = 0; i < FISH_COUNT; i++) {
		if (!booms_2[i].initialize(this, 0, 0, 0, &boomTexture_2))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Boom texture initialization failed"));
		booms_2[i].setX(GAME_WIDTH * 3);
		booms_2[i].setY(GAME_HEIGHT * 3);
		booms_2[i].setScale(BOOM_IMAGE_SCALE);
	}

	//health
	for (int i = 0; i < HEALTH_COUNT; i++) {
		if (!health[i].initialize(graphics, 0, 0, 0, &healthTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Health texture initialization failed"));
		health[i].setX(GAME_WIDTH - (HEALTH_COUNT - i) * health[i].getWidth() * HEALTH_IMAGE_SCALE - 10);
		health[i].setY(10);
		health[i].setScale(HEALTH_IMAGE_SCALE);
	}

	if (!healthBoxTexture.initialize(graphics, HEALTH_BOX_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Health box texture initialization failed"));
	if (!healthBox.initialize(graphics, 0,0,0, &healthBoxTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init health box"));
	healthBox.setX(GAME_WIDTH - (HEALTH_COUNT) * health[0].getWidth() * HEALTH_IMAGE_SCALE - 11);
	healthBox.setY(9);
	healthBox.setScale(HEALTH_BOX_IMAGE_SCALE);

	if(dxFontMedium->initialize(graphics, 42, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{

	if(!displayMenu){

		if(boat.getHealth() < 25) boat.setTextureManager(&boatTexture_25);
		else if(boat.getHealth() < 50) boat.setTextureManager(&boatTexture_50);
		else if(boat.getHealth() < 75) boat.setTextureManager(&boatTexture_75);

		// create bomb on space click
		reloadTime += frameTime;
		if (input->wasKeyPressed(VK_SPACE)){
			if(reloadTime > TIME_TO_RELOAD) {
				int idleBombs = nextIdleBomb();
				if (idleBombs != -1){
					audio->playCue(TNT_SPLASH);
					bombs[idleBombs].setX(boat.getCenterX() - (bombs[idleBombs].getWidth() * BOMB_IMAGE_SCALE) / 2);
					bombs[idleBombs].setY(boat.getY() + boat.getHeight() * BOAT_IMAGE_SCALE);
					bombs[idleBombs].setActive(true);
					bombs[idleBombs].setVisible(true);
					reloadTime = 0;
				}
			}
			input->clearKeyPress(VK_SPACE);
		}

		// update bombs
		for (int i = 0; i < BOMB_COUNT; i++) {
			bombs[i].update(frameTime);
			if (bombs[i].getY() > GAME_HEIGHT) {
				if (bombs[i].getActive()) score -= 100;
				bombs[i].setActive(false);
			}
		}

		//spawn fish
		if (rand() % spawnRate == 0 && fishSpawnCount < FISH_COUNT) {
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
		for (int i = 0; i < FISH_COUNT; i++){
			if (booms_2[i].getActive()){
				booms_2[i].timeOnScreen += frameTime;
				if (booms_2[i].timeOnScreen > 1){
					booms_2[i].setActive(false);
					booms_2[i].setVisible(false);
					booms_2[i].timeOnScreen = 0;
				}
			}
		}
	}
	else{
		if(input->getMouseLButton()){
			if(input->getMouseX() > 465 && input->getMouseX() < 784){
				if(input->getMouseY() > 373 && input->getMouseY() < 445){
					spawnRate = FISH_SPAWN_PROBABILITY_EASY;
					displayMenu = false;
				}
				else if(input->getMouseY() > 493 && input->getMouseY() < 566){
					spawnRate = FISH_SPAWN_PROBABILITY_MEDIUM;
					displayMenu = false;
				}
				else if(input->getMouseY() > 614 && input->getMouseY() < 687){
					spawnRate = FISH_SPAWN_PROBABILITY_HARD;
					displayMenu = false;
				}
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
				audio->playCue(BOOM);
				score += fish[j].getY();
				booms[boomCounter].setX(bombs[i].getCenterX() - booms[i].getWidth() * BOOM_IMAGE_SCALE / 2);
				booms[boomCounter].setY(bombs[i].getY());
				booms[boomCounter].setActive(true);
				booms[boomCounter].setVisible(true);
				boomCounter++;
				if(boomCounter > FISH_COUNT) boomCounter = 0;
				bombs[i].setActive(false);
				bombs[i].setVisible(false);
				fish[j].setActive(false);
				fish[j].setVisible(false);
				fishDead++;
				if(fishDead == FISH_COUNT){
					win();
					winBool = true;
				}
			
			}
		}
	}

	// fish attack boat
	for (int i = 0; i < FISH_COUNT; i++){
		if(fish[i].collidesWith(boat, collisionVector)){
			audio->playCue(EX_SPLASH);
			boat.setHealth(boat.getHealth() - FISH_DAMAGE);
			booms_2[boomCounter_2].setX(fish[i].getCenterX() - booms_2[i].getWidth() * BOOM_IMAGE_SCALE / 2);
			booms_2[boomCounter_2].setY(fish[i].getY() - 32);
			booms_2[boomCounter_2].setActive(true);
			booms_2[boomCounter_2].setVisible(true);
			boomCounter_2++;
			if(boomCounter_2 > FISH_COUNT) boomCounter_2 = 0;
			if(boat.getHealth() == 0) lose();
			fish[i].setActive(false);
			fish[i].setVisible(false);
			fishDead++;
			if(fishDead == FISH_COUNT){
					win();
					winBool = true;
			}
		}
	}


}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	if(displayMenu){
		menu.draw();
	}
	else if(winBool){
		paused = true;
		winScreen.draw();
		dxFontMedium->setFontColor(graphicsNS::RED);
		dxFontMedium->print("Score: " + std::to_string(score),GAME_WIDTH * 0.45, GAME_HEIGHT * 0.9);
	}
	else if(boat.getHealth() > 0) {
		bkg.draw();
		boat.draw();
		for (int i = 0; i < FISH_COUNT; i++) fish[i].draw();
		for (int i = 0; i < BOMB_COUNT; i++) bombs[i].draw();
		for (int i = 0; i < FISH_COUNT; i++) booms[i].draw();
		for (int i = 0; i < FISH_COUNT; i++) booms_2[i].draw();
		for (int i = 0; i < boat.getHealth(); i++) health[i].draw();
		healthBox.draw();
		dxFontMedium->setFontColor(graphicsNS::RED);
		dxFontMedium->print(std::to_string(score),10,6);
		dxFontMedium->print("Fish remaining: " + std::to_string(FISH_COUNT - fishDead),10, GAME_HEIGHT - 50);
	}
	else {
		paused = true;
		gameOver.draw();
		dxFontMedium->setFontColor(graphicsNS::WHITE);
		dxFontMedium->print("Score: " + std::to_string(score),GAME_WIDTH * 0.45, GAME_HEIGHT * 0.9);
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
	fishTexture.onLostDevice();
	bombTexture.onLostDevice();
	boomTexture.onLostDevice();
	boomTexture_2.onLostDevice();
	healthTexture.onLostDevice();
	healthBoxTexture.onLostDevice();
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
	boomTexture_2.onResetDevice();
	boomTexture.onResetDevice();
	healthTexture.onResetDevice();
	healthBoxTexture.onResetDevice();
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

void Spacewar::win() {
	if (!winTexture.initialize(graphics, WIN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Game over texture initialization failed"));
	if (!winScreen.initialize(graphics, 0,0,0, &winTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init game over"));
	winScreen.setX(0);
	winScreen.setY(0);
	winScreen.setScale(GAME_OVER_IMAGE_SCALE);
	score += boat.getHealth() * 250;
}