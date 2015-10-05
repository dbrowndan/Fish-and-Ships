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

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:

	// My defines

	#define SONY_IMAGE_SCALE 0.4
	#define FISH_IMAGE_SCALE 1
	#define BKG_IMAGE_SCALE 0.75
	#define BOAT_IMAGE_SCALE 0.4

// My vars
	TextureManager bkgTexture;
	Image bkg;
	TextureManager boatTexture;
	Boat boat;

	//float boatXVel;

	//int fishSpawnCount;
	//TextureManager fishTexture[FISH_COUNT];
	//Image fish[FISH_COUNT];

	//

	//TextureManager boatTexture;
	//Image boat;

	//struct position{
	//	float xPos;
	//	float yPos;
	//	position() {xPos = 0; yPos = 0;}
	//} boatPos, fishPos[FISH_COUNT];

	//struct velocity{
	//	float xVel;
	//	float yVel;
	//	velocity() { xVel = 0; yVel = 0;}
	//} boatVel, fishVel[FISH_COUNT];

	
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
};

//Stuff for physics


#endif
