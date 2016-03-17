#include <allegro.h>
#include "paddlemove.h"

#define screenWidth 800
#define screenHeight 500
const int image_width = 62;
const int image_height = 100;

void Paddle1Move(int& position, int movespeed)
{
	// Player 1
	if(key[KEY_W] && position > 0) //when we press the W key, it moves the paddle upwards and stops when it reaches the top
		position -= movespeed;
	else if(key[KEY_S] && position < (screenHeight - image_width)) //when we press the S key, it moves the paddle downwards and stops when it reaches the bottom
		position += movespeed;
}

void Paddle2Move(int& position, int movespeed)
{
	//Player 2
	if(key[KEY_UP] && position > 0) //when we press the UP key, it moves the paddle upwards and stops when it reaches the top
		position -= movespeed;
	else if(key[KEY_DOWN] && position < (screenHeight - image_width)) //when we press the DOWN key, it moves the paddle downwards and stops when it reaches the bottom
		position += movespeed;
}