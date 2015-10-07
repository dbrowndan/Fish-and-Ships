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

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	// My defines

	

// My vars
	TextureManager bkgTexture;
	Image bkg;

	TextureManager boatTexture;
	Boat boat;

	TextureManager fishTexture;
	Fish fish[FISH_COUNT];

	TextureManager bombTexture;
	Bomb bombs[BOMB_COUNT];

	int fishSpawnCount;
	int bombsOnScreen;
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
};

//Stuff for physics


#endif
