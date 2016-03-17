#ifndef _INVENTORY
#define _INVENTORY

#include <list>
#include "ball.h"
#include <cassert>
#include <typeinfo>

class Inventory
{
public:
	Inventory(); //Constructor
	Ball* operator[](int index); //Subscript Operator Overloading
	Ball* operator[](int index) const; //Subscript Operator Overloading (for parameters that require the variable to be const)

	template <typename T> //Template function
	void add(T item); //Adds a ball to the list

	void remove(int index); //Removes a ball from the list
	const int get_size(); //Returns the size of the list
	void IncreaseSpeed1(); //For Player 1: Increases Speed of ball heading towards Player 2
	void IncreaseSpeed2(); //For Player 2: Increases Speed of ball heading towards Player 1
	void DecreaseSpeed1(); //For Player 1: Decreases Speed of ball heading towards Player 2
	void DecreaseSpeed2(); //For Player 2: Decreases Speed of ball heading towards Player 1
	Inventory(const Inventory& right); //Copy Constructor
	Inventory& operator=(const Inventory& right); //Assignment Operator
	void clear(); //Deletes all balls and clears all inventory entries
	~Inventory(); //Destructor
private:
	//[20.3] Fundamental Containers
	std::list<Ball*> rack; //List of pointers to balls
	int size; //Size of the list
};

//[16.1] Template Functions
//[16.2] Compile-Time Polymorphism
template <typename T> //Template function
void Inventory::add(T item) //Template function, first makes sure the type is correct, adds element to the list, and increases the size
{
	assert(typeid(item)==typeid(Ball*) || typeid(item)==typeid(RandomBall*) || typeid(item)==typeid(InfluenceBall*) || typeid(item)==typeid(RandomInfluenceBall*));
	rack.push_back(item);
	++size;
}

#endif