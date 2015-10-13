// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "graphics.h"
#include "boat.h"
#include "bomb.h"
#include "fish.h"
#include "boom.h"
#include "textDX.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	TextDX  *dxFontMedium;

	// My defines

	

// My vars
	TextureManager bkgTexture;
	Image bkg;

	TextureManager boatTexture;
	TextureManager boatTexture_75;
	TextureManager boatTexture_50;
	TextureManager boatTexture_25;
	Boat boat;

	TextureManager fishTexture;
	Fish fish[FISH_COUNT];

	TextureManager bombTexture;
	Bomb bombs[BOMB_COUNT];

	TextureManager boomTexture;
	Boom booms[FISH_COUNT];

	TextureManager boomTexture_2;
	Boom booms_2[FISH_COUNT];

	TextureManager healthTexture;
	Image health[HEALTH_COUNT];

	TextureManager healthBoxTexture;
	Image healthBox;

	TextureManager gameOverTexture;
	Image gameOver;

	TextureManager winTexture;
	Image winScreen;

	TextureManager menuTexture;
	Image menu;

	int fishSpawnCount;
	int bombsOnScreen;
	float reloadTime;
	int boomCounter;
	int boomCounter_2;
	bool displayMenu;
	int spawnRate;
	int score;
	bool winBool;
	int fishDead;

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	int nextIdleBomb();
	void lose();
	void win();
};

//Stuff for physics


#endif
