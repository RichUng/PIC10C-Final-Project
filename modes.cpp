#include "modes.h"

//Mode A: Adds a influence ball after a player gets a point and old ball is deleted
//Note: Influence functions are omitted to make the ball "normal"
void ModeA(Inventory& it)
{
	if(it.get_size() == 0)
		it.add(new InfluenceBall);
}

//Mode B: Adds a random ball after a player gets a point and old ball is deleted
void ModeB(Inventory& it)
{
	if(it.get_size() == 0)
		it.add(new RandomBall);
}

//Mode C: Adds a influence ball after a player gets a point and old ball is deleted
//Note: Influence functions are included to make the ball "influenced"
void ModeC(Inventory& it)
{
	if(it.get_size() == 0)
		it.add(new InfluenceBall);
	if(key[KEY_A])
		it.DecreaseSpeed1();
	if(key[KEY_D])
		it.IncreaseSpeed1();
	if(key[KEY_LEFT])
		it.IncreaseSpeed2();
	if(key[KEY_RIGHT])
		it.DecreaseSpeed2();
}

//Mode D: Adds a randominfluence ball after a player gets a point and old ball is deleted
//Note: Influence functions are included to make the ball "influenced"
void ModeD(Inventory& it)
{
	if(it.get_size() == 0)
		it.add(new RandomInfluenceBall);
	if(key[KEY_A])
		it.DecreaseSpeed1();
	if(key[KEY_D])
		it.IncreaseSpeed1();
	if(key[KEY_LEFT])
		it.IncreaseSpeed2();
	if(key[KEY_RIGHT])
		it.DecreaseSpeed2();
}

//Mode E: Keys E, R, and T allow you to add multiple balls into the gameplay.
//Note: Influence functions are included to make the ball "influenced"
void ModeE(Inventory& it, bool& keydown)
{
	if(key[KEY_E] && keydown == false)
	{
		it.add(new RandomBall);
		keydown = true;
	}
	if(key[KEY_R] && keydown == false)
	{
		it.add(new InfluenceBall);
		keydown = true;
	}
	if(key[KEY_T] && keydown == false)
	{
		it.add(new RandomInfluenceBall);
		keydown = true;
	}
	if(!key[KEY_E] && !key[KEY_R] && !key[KEY_T])
		keydown = false;

	if(key[KEY_A])
		it.DecreaseSpeed1();
	if(key[KEY_D])
		it.IncreaseSpeed1();
	if(key[KEY_LEFT])
		it.IncreaseSpeed2();
	if(key[KEY_RIGHT])
		it.DecreaseSpeed2();
}