#ifndef _PADDLEMOVE
#define _PADDLEMOVE

//make Player 1's paddle move
//we passed the position by reference because we have to change the actual Position[0][1] in main
void Paddle1Move(int& position, int movespeed);

//make Player 2's paddle move
//we passed the position by reference because we have to change the actual Position[1][1] in main
void Paddle2Move(int& position, int movespeed);

#endif