#ifndef _SELECTSCREEN
#define _SELECTSCREEN

#include <allegro.h>
#include <string>

#define screenWidth 800
#define screenHeight 500

//shows the selection screen
void select_screen(bool& before_start, std::string& letter_input, bool& keydown, BITMAP*& select);

#endif