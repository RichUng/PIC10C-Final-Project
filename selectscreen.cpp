#include <allegro.h>
#include <string>
#include "selectscreen.h"

void select_screen(bool& before_start, std::string& letter_input, bool& keydown, BITMAP*& select)
{
	std::string welcome = "TOTALLY AWESOME PING PONG GAME";
	std::string modes = "MODES";
	std::string a = "A. Normal";
	std::string b = "B. Random Ball";
	std::string c = "C. Influence Ball";
	std::string d = "D. Random Influence Ball";
	std::string e = "E. Free For All";

	//output the selection screen list of modes that the user can choose from
	textout_centre_ex(select, font, welcome.c_str(), screenWidth/2, screenHeight/6, makecol(255,0,0), makecol(0,0,0));
	textout_centre_ex(select, font, modes.c_str(), screenWidth/2, screenHeight/2 - 70, makecol(0,255,0), makecol(0,0,0));
	textout_ex(select, font, a.c_str(), screenWidth/2 - 80, screenHeight/2 - 50, makecol(255,255,255), makecol(0,0,0));
	textout_ex(select, font, b.c_str(), screenWidth/2 - 80, screenHeight/2 - 40, makecol(255,255,255), makecol(0,0,0));
	textout_ex(select, font, c.c_str(), screenWidth/2 - 80, screenHeight/2 - 30, makecol(255,255,255), makecol(0,0,0));
	textout_ex(select, font, d.c_str(), screenWidth/2 - 80, screenHeight/2 - 20, makecol(255,255,255), makecol(0,0,0));
	textout_ex(select, font, e.c_str(), screenWidth/2 - 80, screenHeight/2 - 10, makecol(255,255,255), makecol(0,0,0));

	//if whichever letter is pressed (between A - E), then a certain mode will be selected
	if(key[KEY_A])
	{
		before_start = false;
		letter_input = "A";
		keydown = true;
	} 
	else if(key[KEY_B])
	{
		before_start = false;
		letter_input = "B";
		keydown = true;
	}
	else if(key[KEY_C])
	{
		before_start = false;
		letter_input = "C";
		keydown = true;
	}
	else if(key[KEY_D])
	{
		before_start = false;
		letter_input = "D";
		keydown = true;
	}
	else if(key[KEY_E])
	{
		before_start = false;
		letter_input = "E";
		keydown = true;
	}
}