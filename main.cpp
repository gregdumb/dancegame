#include <iostream>
#include "dance.h"

Fl_Double_Window* win;

// Creates an array of images we will use for our backgrounds
Fl_JPEG_Image* i_background [2];

// Arrow key images
Fl_PNG_Image* i_key_up;
Fl_PNG_Image* i_key_down;
Fl_PNG_Image* i_key_left;
Fl_PNG_Image* i_key_right;

int Game_Window::handle(int e)
{
	return 0;
}

// Sets our image variables to actual image files
void loadImages()
{
	// Backgrounds
	i_background[0] = new Fl_JPEG_Image("res/bg/bg_1.jpg");
	i_background[1] = new Fl_JPEG_Image("res/bg/bg_2.jpg");
	
	// Keys
	i_key_up = new Fl_PNG_Image("res/keys/up_key.png");
	i_key_down = new Fl_PNG_Image("res/keys/down_key.png");
	i_key_left = new Fl_PNG_Image("res/keys/left_key.png");
	i_key_right = new Fl_PNG_Image("res/keys/right_key.png");
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

// Opens a new level
// WARNING: level numbers start at 0, not 1!!!
void loadLevel(int levelNum)
{
	box_background->image(i_background[levelNum]);
	box_key->image(i_key_up);
}

int main()
{
	win = make_window();
	win->show();

	loadImages();
	loadLevel(0);

	Fl::run();
}
