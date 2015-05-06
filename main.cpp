#include <iostream>
#include <sstream>
#include <stdlib.h>
//#include <FL/fl_draw.H>
#include <time.h>
#include "dance.h"

Game_Window* game_win;
Fl_Double_Window* menu_win;
Fl_Double_Window* help_win;

// Creates an array of images we will use for our backgrounds
Fl_JPEG_Image* i_background [2];
Fl_PNG_Image* i_presstostart;
Fl_PNG_Image* i_key_bg;

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

		else if(Fl::event_key() == 32) // Key for spacebar
			startPlaying();

		else
			incorrectKeyPressed = true;

		std::cout << Fl::event_key() << std::endl;
	}

	return 0;
}

void loadBackgrounds()
{
	i_background[0] = new Fl_JPEG_Image("res/bg/bg_1.jpg");
	i_background[1] = new Fl_JPEG_Image("res/bg/bg_2.jpg");
	
	i_presstostart = new Fl_PNG_Image("res/bg/spacebar.png");
	i_key_bg = new Fl_PNG_Image("res/bg/bg_key.png");
}

void loadArrowKeys()
{
	i_key_up = new Fl_PNG_Image("res/keys/up_key.png");
	i_key_down = new Fl_PNG_Image("res/keys/down_key.png");
	i_key_left = new Fl_PNG_Image("res/keys/left_key.png");
	i_key_right = new Fl_PNG_Image("res/keys/right_key.png");
}

const int carlton_N = 24;
const int justin_N = 25;
const int mj_N = 9;
const int snoop_N = 19;
Fl_GIF_Image* carlton_images[carlton_N]; // frames are 0-23
Fl_GIF_Image* justin_images[justin_N]; // frames are 0-24
Fl_GIF_Image* mj_images[mj_N]; // frames are 0-8
Fl_GIF_Image* snoop_images[snoop_N]; // frames are 0-18

void loadGifs()
{
     for(int i = 0; i < carlton_N; i++)
     {
       std::ostringstream oss;
       oss << "res/dancers/carlton/carlton" << i << ".gif";
       carlton_images[i] = new Fl_GIF_Image(oss.str().c_str());
     }

     for(int i = 0; i < justin_N; i++)
     {
       std::ostringstream oss;
       oss << "res/dancers/justin/justin" << i << ".gif";
       justin_images[i] = new Fl_GIF_Image(oss.str().c_str());
     }

     for(int i = 0; i < mj_N; i++)
     {
       std::ostringstream oss;
       oss << "res/dancers/michael/mj" << i << ".gif";
       mj_images[i] = new Fl_GIF_Image(oss.str().c_str());
     }

     for(int i = 0; i < snoop_N; i++)
     {
       std::ostringstream oss;
       oss << "res/dancers/snoop/snoop" << i << ".gif";
       snoop_images[i] = new Fl_GIF_Image(oss.str().c_str());
     }
 
}

void animate_carlton(void*)
{
     static int i = 0;
     i = (i + 1) % carlton_N;
}
void animate_justin(void*)
{
     static int i = 0;
     i = (i + 1) % justin_N;
}
void animate_mj(void*)
{
     static int i = 0;
     i = (i + 1) % mj_N;
}
void animate_snoop(void*)
{
     static int i = 0;
     i = (i + 1) % snoop_N;
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
	game_win->box_background->image(i_background[levelNum]);
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

	game_win->box_key->image(newArrow);
	game_win->redraw();
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

// Sets up everything we need to play
void loadGameWindow()
{
	loadImages();
	loadLevel(0);

	game_win->box_presstostart->image(i_presstostart);

	game_win->show();

	//Fl::add_timeout(1.0, beginKeypressSequence);
}

// When the user presses spacebar, this will start playing the game
void startPlaying()
{
	Fl::add_timeout(0.2, beginKeypressSequence);
	game_win->box_presstostart->image(i_key_bg);
}

int main()
{
	game_win = make_game_window();
	//game_win->show();

	menu_win = make_menu_window();
	menu_win->show();

	help_win = make_help_window();

        //loadGifs();

	// Initialize the images
	//loadImages();

	// Load the first level (this is clunky, the main menu 
	// "play" button should be handling this, not main() ).
	//loadLevel(0);

	// We need this for random numbers, ignore it
	initRandomSeed();
	
	// Sets timer to start showing the keys
	//Fl::add_timeout(1.0, beginKeypressSequence);

	Fl::run();
}
