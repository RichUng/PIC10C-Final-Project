#include "inventory.h"
#include "ball.h"
#include <typeinfo>

//[20.2] Iterators (in almost every function in this file)

//[15.3] Constructors 
Inventory::Inventory()
{
	size = 0; //Initializes size to 0
};

//[14.7] Subscript
Ball* Inventory::operator[](int index)
{
	//Uses an iterator to go to the correct index (returns NULL if it reaches the end) and returns the value
	std::list<Ball*>::iterator scan = rack.begin();
	for(int i = 0; i < index; i++)
	{
		if(scan != rack.end())
			scan++;
	}
	return *scan;
}

//[14.7] Subscript
Ball* Inventory::operator[](int index) const
{
	//Uses an iterator to go to the correct index (returns NULL if it reaches the end) and returns the value
	std::list<Ball*>::const_iterator scan = rack.begin();
	for(int i = 0; i < index; i++)
	{
		if(scan != rack.end())
			scan++;
	}
	return *scan;
}

void Inventory::remove(int index)
{
	//Uses an iterator to go to the correct index (returns NULL if it reaches the end), deletes the value, and decrements the size
	std::list<Ball*>::const_iterator scan = rack.begin();
	for(int i = 0; i < index; i++)
	{
		if(scan != rack.end())
			scan++;
	}
	delete *scan;
	rack.erase(scan);
	--size;
}

const int Inventory::get_size()
{
	//Returns the size of the list
	return size;
}

//[19.3] Obtaining run-time type information
void Inventory::IncreaseSpeed1()
{
	//Changes speed of all balls only if the ball is an InfluenceBall or RandomInfluenceBall (only they have the function)
	std::list<Ball*>::iterator scan = rack.begin();
	for(scan = rack.begin(); scan!=rack.end(); scan++)
	{
		if(typeid(*(*scan)) == typeid(InfluenceBall))
			dynamic_cast<InfluenceBall*>(*scan)->IncreaseSpeed1();
		if(typeid(*(*scan)) == typeid(RandomInfluenceBall))
			dynamic_cast<RandomInfluenceBall*>(*scan)->IncreaseSpeed1();
	}
}

//[19.3] Obtaining run-time type information
void Inventory::IncreaseSpeed2()
{
	//Changes speed of all balls only if the ball is an InfluenceBall or RandomInfluenceBall (only they have the function)
	std::list<Ball*>::iterator scan = rack.begin();
	for(scan = rack.begin(); scan!=rack.end(); scan++)
	{
		if(typeid(*(*scan)) == typeid(InfluenceBall))
			dynamic_cast<InfluenceBall*>(*scan)->IncreaseSpeed2();
		if(typeid(*(*scan)) == typeid(RandomInfluenceBall))
			dynamic_cast<RandomInfluenceBall*>(*scan)->IncreaseSpeed2();
	}
}

//[19.3] Obtaining run-time type information
void Inventory::DecreaseSpeed1()
{
	//Changes speed of all balls only if the ball is an InfluenceBall or RandomInfluenceBall (only they have the function)
	std::list<Ball*>::iterator scan = rack.begin();
	for(scan = rack.begin(); scan!=rack.end(); scan++)
	{
		if(typeid(*(*scan)) == typeid(InfluenceBall))
			dynamic_cast<InfluenceBall*>(*scan)->DecreaseSpeed1();
		if(typeid(*(*scan)) == typeid(RandomInfluenceBall))
			dynamic_cast<RandomInfluenceBall*>(*scan)->DecreaseSpeed1();
	}
}

//[19.3] Obtaining run-time type information
void Inventory::DecreaseSpeed2()
{
	//Changes speed of all balls only if the ball is an InfluenceBall or RandomInfluenceBall (only they have the function)
	std::list<Ball*>::iterator scan = rack.begin();
	for(scan = rack.begin(); scan!=rack.end(); scan++)
	{
		if(typeid(*(*scan)) == typeid(InfluenceBall))
			dynamic_cast<InfluenceBall*>(*scan)->DecreaseSpeed2();
		if(typeid(*(*scan)) == typeid(RandomInfluenceBall))
			dynamic_cast<RandomInfluenceBall*>(*scan)->DecreaseSpeed2();
	}
}

//[19.3] Obtaining run-time type information
Inventory::Inventory(const Inventory& right)
{
	//Checks if parameter is the same object to see if anything needs to be done
	if (this != &right)
	{
		//Goes through the list and deletes all the ball pointers
		std::list<Ball*>::iterator scan;
		for(scan = rack.begin(); scan!=rack.end(); scan++)
		{
			delete *scan;
			*scan = NULL;
		}
		//Clears the list of ball pointers
		rack.clear();

		//Goes through the right list's ball pointers, dereferences the pointer,
		//sets it equal to the push pointer, and pushes the pointer back
		//typeid and dymanic_cast is done to properly push back the dereferenced value.
		for(int i = 0; i < right.size; i++)
		{
			if(typeid(*(right[i])) == typeid(RandomBall))
			{
				RandomBall* push = new RandomBall;
				*push = *(dynamic_cast<RandomBall*>(right[i]));
				rack.push_back(push);
			}
			if(typeid(*(right[i])) == typeid(InfluenceBall))
			{
				InfluenceBall* push = new InfluenceBall;
				*push = *(dynamic_cast<InfluenceBall*>(right[i]));
				rack.push_back(push);
			}
			if(typeid(*(right[i])) == typeid(RandomInfluenceBall))
			{
				RandomInfluenceBall* push = new RandomInfluenceBall;
				*push = *(dynamic_cast<RandomInfluenceBall*>(right[i]));
				rack.push_back(push);
			}
		}
	}
};

//[14.5] Assignment
//[19.3] Obtaining run-time type information
Inventory& Inventory::operator=(const Inventory& right)
{
	//Checks if right value is the same object to see if anything needs to be done
	if (this != &right)
	{
		//Goes through the list and deletes all the ball pointers
		std::list<Ball*>::iterator scan = rack.begin();
		for(scan = rack.begin(); scan!=rack.end(); scan++)
		{
			delete *scan;
			*scan = NULL;
		}

		//Clears the list of ball pointers
		rack.clear();

		//Goes through the right list's ball pointers, dereferences the pointer,
		//sets it equal to the push pointer, and pushes the pointer back
		//typeid and dymanic_cast is done to properly push back the dereferenced value.
		for(int i = 0; i < right.size; i++)
		{
			if(typeid(*(right[i])) == typeid(RandomBall))
			{
				RandomBall* push = new RandomBall;
				*push = *(dynamic_cast<RandomBall*>(right[i]));
				rack.push_back(push);
			}
			if(typeid(*(right[i])) == typeid(InfluenceBall))
			{
				InfluenceBall* push = new InfluenceBall;
				*push = *(dynamic_cast<InfluenceBall*>(right[i]));
				rack.push_back(push);
			}
			if(typeid(*(right[i])) == typeid(RandomInfluenceBall))
			{
				RandomInfluenceBall* push = new RandomInfluenceBall;
				*push = *(dynamic_cast<RandomInfluenceBall*>(right[i]));
				rack.push_back(push);
			}
		}
	}
	return *this;
};

void Inventory::clear()
{
	//Goes through the list and deletes all the pointers. Then finally clears the list.
	std::list<Ball*>::iterator scan;
	for(scan = rack.begin(); scan!=rack.end(); scan++)
	{
		delete *scan;
		*scan = NULL;
	}
	rack.clear();
}

//[15.4] Destructors 
Inventory::~Inventory()
{
	//Goes through the list and deletes all the pointers. Then finally clears the list.
	//[20.2] Iterators
	std::list<Ball*>::iterator scan;
	for(scan = rack.begin(); scan!=rack.end(); scan++)
	{
		delete *scan;
		*scan = NULL;
	}
	rack.clear();
};