#ifndef _OBSTACLE
#define _OBSTACLE

#include <allegro.h>
#include "inventory.h"
#include <typeinfo>
#include <cassert>

//[16.3] Template Classes
//[16.4] Turning a Class into a Template
//[16.5] Non-type Template Parameters (template <typename T, int N>)
template<typename T, int N>
class Obstacle
{
public:
	Obstacle();
	void reflect(Inventory& it);
private:
	T type; //Stores the type of the object into a private variable.
	int player; //Equal to parameter N, determines what player obstacle influences
	//Following code describes the location of the obstacle (it's in the shape of a square)
	int size; //Length and width of the obstacle
	int x; //Upper left x-coordinate of the obstacle
	int y; //Upper left y-coordinate of the obstacle
};

template<typename T, int N>
Obstacle<T, N>::Obstacle()
{
	//Verifies that the template parameters are valid
	assert(N == 0 || N == 1 || N == 2);
	assert(typeid(T)==typeid(RandomBall) || typeid(T)==typeid(InfluenceBall) || typeid(T)==typeid(RandomInfluenceBall));

	//Sets the second parameter to the player it influences, the size, and the location of the obstacle
	player = N;
	size = 200;
	x = 300;
	y = 100;
}

template<typename T, int N>
void Obstacle<T, N>::reflect(Inventory& it)
{
	//Goes through the entire list of balls in the inventory
	for(int i = 0; i < it.get_size(); i++)
	{
		//Verifies that the ball matches the obstacle's type
		if(typeid(*(it[i])) == typeid(type))
		{
			//Verfies that the ball is within the x-coordinates of the obstacle
			if(it[i]->get_x() >= x && it[i]->get_x() <= (x+size))
			{
				//Verifies that the ball is within the y-coordinates of the obstacle
				if(it[i]->get_y() >= y && it[i]->get_y() <= (y+size))
				{
					//If player = 0, obstacle applies to both players
					//Ball randomly teleports to one of the four corners
					//of the obstacle box
					if(player == 0)
					{
						//Within each if statement, x0, y0, v0x, v0y, t, ax, and ay
						//are reset/changed accordingly to "teleport"
						int teleport = rand() % 4;
						if(teleport == 0)
						{
							it[i]->set_x0(x);
							it[i]->set_y0(y);
							it[i]->set_v0x(-abs(it[i]->get_ax()*it[i]->get_t()+it[i]->get_v0x()));
							it[i]->set_v0y(-abs(it[i]->get_ay()*it[i]->get_t()+it[i]->get_v0y()));
							it[i]->reset_t();
							it[i]->set_ax(-abs(it[i]->get_ax()));
							it[i]->set_ay(-abs(it[i]->get_ay()));
						}
						if(teleport == 1)
						{
							it[i]->set_x0(x+size);
							it[i]->set_y0(y);
							it[i]->set_v0x(abs(it[i]->get_ax()*it[i]->get_t()+it[i]->get_v0x()));
							it[i]->set_v0y(-abs(it[i]->get_ay()*it[i]->get_t()+it[i]->get_v0y()));
							it[i]->reset_t();
							it[i]->set_ax(abs(it[i]->get_ax()));
							it[i]->set_ay(-abs(it[i]->get_ay()));
						}
						if(teleport == 2)
						{
							it[i]->set_x0(x);
							it[i]->set_y0(y+size);
							it[i]->set_v0x(-abs(it[i]->get_ax()*it[i]->get_t()+it[i]->get_v0x()));
							it[i]->set_v0y(abs(it[i]->get_ay()*it[i]->get_t()+it[i]->get_v0y()));
							it[i]->reset_t();
							it[i]->set_ax(-abs(it[i]->get_ax()));
							it[i]->set_ay(abs(it[i]->get_ay()));
						}
						if(teleport == 3)
						{
							it[i]->set_x0(x+size);
							it[i]->set_y0(y+size);
							it[i]->set_v0x(abs(it[i]->get_ax()*it[i]->get_t()+it[i]->get_v0x()));
							it[i]->set_v0y(abs(it[i]->get_ay()*it[i]->get_t()+it[i]->get_v0y()));
							it[i]->reset_t();
							it[i]->set_ax(abs(it[i]->get_ax()));
							it[i]->set_ay(abs(it[i]->get_ay()));
						}
					}
					//If obstacle applies to player 1, ball heading towards player 2
					//that hits the obstacle will head back to player 1
					if(player == 1)
					{
						it[i]->set_v0x(-abs(it[i]->get_ax()*it[i]->get_t()+it[i]->get_v0x()));
						it[i]->reset_t();
						it[i]->set_ax(-abs(it[i]->get_ax()));
						it[i]->set_y0(it[i]->get_y());
						it[i]->set_x0(it[i]->get_x());
					}
					//If obstacle applies to player 2, ball heading towards player 1
					//that hits the obstacle will head back to player 2
					if(player == 2)
					{
						it[i]->set_v0x(abs(it[i]->get_ax()*it[i]->get_t()+it[i]->get_v0x()));
						it[i]->reset_t();
						it[i]->set_ax(abs(it[i]->get_ax()));
						it[i]->set_y0(it[i]->get_y());
						it[i]->set_x0(it[i]->get_x());
					}
				}
			}
		}
	}
}

#endif