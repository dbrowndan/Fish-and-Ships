// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 5 constants.h v1.0
#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
//gameplay
const int FISH_COUNT = 200;
const int FISH_SPAWN_PROBABILITY_EASY = 280;
const int FISH_SPAWN_PROBABILITY_MEDIUM = 180;
const int FISH_SPAWN_PROBABILITY_HARD = 120;
const int BOMB_COUNT = 5;
const float TIME_TO_RELOAD = 0.5;
const float FISH_SPEED_SLOW = 100;
const float FISH_SPEED_MEDIUM = 200;
const float FISH_SPEED_FAST = 300;
const float FISH_ATTACK_TIME = 0.4;
const float BOAT_SPEED = 2000;
const int HEALTH_COUNT = 100;
const int FISH_DAMAGE = 5;

// graphic images
const char BKG_IMAGE[] = "pictures\\bkg.jpg";
const char BOAT_IMAGE[] = "pictures\\boat.png";
const char BOAT_IMAGE_75[] = "pictures\\boat_75.png";
const char BOAT_IMAGE_50[] = "pictures\\boat_50.png";
const char BOAT_IMAGE_25[] = "pictures\\boat_25.png";
const char FISH_IMAGE[] = "pictures\\fish.png";
const char BOMB_IMAGE[] = "pictures\\bomb_2.png";
const char BOOM_IMAGE[] = "pictures\\boom.png";
const char HEALTH_IMAGE[] = "pictures\\health.png";
const char HEALTH_BOX_IMAGE[] = "pictures\\healthBox.png";
const char GAME_OVER_IMAGE[] = "pictures\\gameover.png";
const char WIN_IMAGE[] = "pictures\\youwin.png";
const char MENU_IMAGE[] = "pictures\\menu.png";
const char BOOM_IMAGE_2[] = "pictures\\boom_2.png";

// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// audio cues
const char BKG_MUSIC[] = "sea shanty";
const char TNT_SPLASH[] = "tntSplash";
const char EX_SPLASH[] = "exSplash";
const char BOOM[] = "boom";

// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Spacewar";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  1366;               // width of game in pixels
const UINT GAME_HEIGHT = 768;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key

//defines
#define SONY_IMAGE_SCALE 0.4
#define FISH_IMAGE_SCALE 1
#define BKG_IMAGE_SCALE 0.75
#define BOAT_IMAGE_SCALE 0.4
#define BOMB_IMAGE_SCALE 0.08
#define BOOM_IMAGE_SCALE 0.175
#define HEALTH_IMAGE_SCALE 1
#define HEALTH_BOX_IMAGE_SCALE 1
#define GAME_OVER_IMAGE_SCALE 0.75


#endif
