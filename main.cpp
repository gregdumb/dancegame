#include <iostream>
#include "dance.h"

Fl_Double_Window* win;

using namespace std;

int main()
{
	win = make_window();
	win->show();
	Fl::run();

	cout << "Hello World" << endl;
	cout << "This is a test of github";
}
