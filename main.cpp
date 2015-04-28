#include <iostream>
#include "dance.h"

Fl_Double_Window* win;

// Creates an array of images we will use for our backgrounds
Fl_JPEG_Image* i_background [2];

// Sets our image variables to actual image files
void loadImages()
{
	i_background[0] = new Fl_JPEG_Image("res/bg/bg_1.jpg");
	i_background[1] = new Fl_JPEG_Image("res/bg/bg_2.jpg");
}

// Opens a new level
// WARNING: level numbers start at 0, not 1!!!
void loadLevel(int levelNum)
{
	box_background->image(i_background[levelNum]);
}

int main()
{
	win = make_window();
	win->show();

	loadImages();
	loadLevel(0);

	Fl::run();
}
