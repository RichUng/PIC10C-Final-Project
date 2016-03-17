#include <allegro.h>
#include <string>
#include "gameover.h"

#define screenWidth 800
#define screenHeight 500

//displays game over message to screen
//if player 1 wins, display it
//if player 2 wins, display it
//if it's a tie, display it
void gameOver(int& player1score, int& player2score, BITMAP*& Buffer)
{
	std::string game_over = "Game Over! =(";
	std::string player1wins = "Player 1 Wins!";
	std::string player2wins = "Player 2 Wins!";
	std::string tie = "It's a tie!";
	textout_centre_ex(Buffer, font, game_over.c_str(), screenWidth/2, screenHeight/6 + 20, makecol(255,0,0), makecol(0,0,0));
	if(player1score > player2score)
		textout_centre_ex(Buffer, font, player1wins.c_str(), screenWidth/2, screenHeight/6 + 40, makecol(255,0,0), makecol(0,0,0));
	else if(player1score < player2score)
		textout_centre_ex(Buffer, font, player2wins.c_str(), screenWidth/2, screenHeight/6 + 40, makecol(255,0,0), makecol(0,0,0));
	else
		textout_centre_ex(Buffer, font, tie.c_str(), screenWidth/2, screenHeight/6 + 40, makecol(255,0,0), makecol(0,0,0));
}