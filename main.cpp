#include <iostream>
#include "dance.h"

Fl_Double_Window* win;

using namespace std;

Fl_JPEG_Image* i_background_lvl1;

void loadImages()
{
	i_background_lvl1 = new Fl_JPEG_Image("res/bg/bg_1.jpg");
	box_background->image(i_background_lvl1);
}

int main()
{
	win = make_window();
	win->show();

	loadImages();

	Fl::run();
}
