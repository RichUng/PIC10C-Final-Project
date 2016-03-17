#include "checkwin.h"

#define screenWidth 800
#define screenHeight 500

void CheckWin(Inventory& x, int& player1score, int& player2score, bool& continue_game)
{
	for(int i=0; i<x.get_size(); i++)
	{
		if(x[i]->get_x() > screenWidth) //Player 1 Wins
		{
			++player1score; //adds +1 to player 1 score
			x.remove(i);
		}
		else if(x[i]->get_x() < 0) //Player 2 Wins
		{
			++player2score; //adds +1 to player 2 score
			x.remove(i);
		}
	}
}