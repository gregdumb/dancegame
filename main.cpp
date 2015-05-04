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

bool correctKeyPressed;
bool incorrectKeyPressed;
int expectedKey = 0;

int Game_Window::handle(int e)
{
	// 12 is the code for FL_KEYDOWN, 65364 is the code for down arrow.
	if(e == 12 && Fl::event_key() == expectedKey)
		correctKeyPressed = true;

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

// Sets our image variables to actual image files
void loadImages()
{
	loadBackgrounds();
	loadArrowKeys();
}

// Opens a new level
// WARNING: level numbers start at 0, not 1!!!
void loadLevel(int levelNum)
{
	win->box_background->image(i_background[levelNum]);
	//win->box_key->image(i_key_up);
}

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

	lastNum = randNum;

	Fl_PNG_Image* newArrow;

	// Pick a new arrow from the number.
	if(randNum == 1)
	{
		newArrow = i_key_up;
		expectedKey = 65362;
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

void timerExpire(void*);

// Start a new timeout
void setNewTimer()
{
	correctKeyPressed = false;
	popupRandomArrow();
	Fl::add_timeout(1.0, timerExpire);
}

void timerExpire(void*)
{
	if(correctKeyPressed)
		setNewTimer();
}

void initRandomSeed()
{
	srand(time(NULL));
}

int main()
{
	win = make_window();
	win->show();

	loadImages();
	loadLevel(0);

	initRandomSeed();
	setNewTimer();

	Fl::run();
}
