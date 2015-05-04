#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "dance.h"

Game_Window* win;

// Creates an array of images we will use for our backgrounds
Fl_JPEG_Image* i_background [2];

// Arrow key images
Fl_PNG_Image* i_key_up;
Fl_PNG_Image* i_key_down;
Fl_PNG_Image* i_key_left;
Fl_PNG_Image* i_key_right;

// These are used for calculating whether or not the right
// key was pressed.
bool correctKeyPressed;
bool incorrectKeyPressed;
int expectedKey = 0;

// When any event happens, this is called.  "e" is the code for
// the type of event.
int Game_Window::handle(int e)
{
	// "12" is the code for "a key was pushed down"
	if(e == 12)
	{
		// Compare the pressed key with the key that we 
		// were supposed to press
		if(Fl::event_key() == expectedKey)
			correctKeyPressed = true;
		else
			incorrectKeyPressed = true;
	}

	return 0;
}

void loadBackgrounds()
{
	i_background[0] = new Fl_JPEG_Image("res/bg/bg_1.jpg");
	i_background[1] = new Fl_JPEG_Image("res/bg/bg_2.jpg");
}

void loadArrowKeys()
{
	i_key_up = new Fl_PNG_Image("res/keys/up_key.png");
	i_key_down = new Fl_PNG_Image("res/keys/down_key.png");
	i_key_left = new Fl_PNG_Image("res/keys/left_key.png");
	i_key_right = new Fl_PNG_Image("res/keys/right_key.png");
}

void loadGifs()
{
	// HUDA PUT YOUR STUFF HERE
}

// Sets our image variables to actual image files.
// This will NOT actually set the background of the window
// to anything, see loadLevel for that.
void loadImages()
{
	loadBackgrounds();
	loadArrowKeys();
	loadGifs();
}

// Opens a new level
// WARNING: level numbers start at 0, not 1!!!
// This function is mostly empty right now, we need to 
// fix it so it changes the GIF as well as the background.
void loadLevel(int levelNum)
{
	win->box_background->image(i_background[levelNum]);
}

// Changes the arrow on the screen.  Completely randomly chosen,
// but it will never choose the same arrow twice in a row.
void popupRandomArrow()
{
	// This will be used so we don't get the same arrow twice in a row.
	static int lastNum = 0;

	// Generate a new random number.
	int randNum = randNum = rand() % 4 + 1;

	// Do this so we don't get the same arrow
	// twice in a row.
	while(randNum == lastNum)
		randNum = rand() % 4 + 1;

	// Next cycle, lastNum will equal whatever the randNum was this
	// cycle.  That way we know what the number was this cycle, 
	// so we can avoid it next time.
	lastNum = randNum;

	Fl_PNG_Image* newArrow;

	// Pick a new arrow from the number.
	if(randNum == 1)
	{
		newArrow = i_key_up;
		expectedKey = 65362; // These strange numbers are
				     // the codes for the arrow keys.
	}
	else if(randNum == 2)
	{
		newArrow = i_key_down;
		expectedKey = 65364;
	}
	else if(randNum == 3)
	{
		newArrow = i_key_left;
		expectedKey = 65361;
	}
	else
	{
		newArrow = i_key_right;
		expectedKey = 65363;
	}

	win->box_key->image(newArrow);
	win->redraw();
}

// This has to be here so c++ can see it, even though it is
// defined later.
void timerExpire(void*);

// Start a new timeout
void setNewTimer()
{
	correctKeyPressed = false;
	popupRandomArrow();
	Fl::add_timeout(1.0, timerExpire);
}

// When the time to press the key runs out, this will check
// if we actually pressed it or not.
void timerExpire(void*)
{
	if(correctKeyPressed && !incorrectKeyPressed)
		setNewTimer();
}

// For random numbers, c++ needs this, ignore it.
void initRandomSeed()
{
	srand(time(NULL));
}

// Starts showing the keys
void beginKeypressSequence(void*)
{
	setNewTimer();
}

int main()
{
	win = make_window();
	win->show();

	// Initialize the images
	loadImages();

	// Load the first level (this is clunky, the main menu 
	// "play" button should be handling this, not main() ).
	loadLevel(0);

	// We need this for random numbers, ignore it
	initRandomSeed();
	
	// Sets timer to start showing the keys
	Fl::add_timeout(1.0, beginKeypressSequence);

	Fl::run();
}
