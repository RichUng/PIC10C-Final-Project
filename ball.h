#ifndef _BALL
#define _BALL

#include <iostream>
#include <allegro.h>
#include <cstdlib>

class Ball //Abstract Class
{
public:
	Ball(); //Ball Constructor
	const int get_x(); //Returns x coordinate of ball
	const int get_y(); //Returns y coordinate of ball

	const double get_ax()
	{
		return ax;
	}
	const double get_ay()
	{
		return ay;
	}
	const double get_t()
	{
		return t;
	}
	const double get_v0x()
	{
		return v0x;
	}
	const double get_v0y()
	{
		return v0y;
	}
	void set_y0(double value)
	{
		y0 = value;
	}
	void set_x0(double value)
	{
		x0 = value;
	}
	void set_v0x(double value)
	{
		v0x = value;
	}
	void set_v0y(double value)
	{
		v0y = value;
	}
	void set_ax(double value)
	{
		ax = value;
	}
	void set_ay(double value)
	{
		ay = value;
	}
	void reset_t()
	{
		t = 0;
	}

	//[19.2] Abstract Classes (Ball's an abstract class)
	virtual void BallBounce(int& player1, int& player2) = 0; //Virtual function makes this an abstract class
	virtual void BallMove(int& player1, int& player2) = 0; //Virtual function makes this an abstract class

	void draw(BITMAP* Buffer); //Draws the ball onto the Buffer
	Ball(const Ball& right); //Copy Constructor
	Ball& operator=(const Ball& right); //Assignment Operator
	virtual ~Ball(); //Virtual Destructor to properly destruct derived classes
//[18.3] Protected scope
protected:
	double ax; //X Acceleration
	double ay; //Y Acceleration
	double vx; //Current X Velocity
	double vy; //Current Y Velocity
	BITMAP* image; //Ball's image
	int ballsize; //Ball Dimension
	double t; //time of the ball (to make this a typical physics problem)
	double x0; //Initial X Position of Ball
	double y0; //Initial Y Position of Ball
	double v0x; //Initial X Velocity of Ball
	double v0y; //Initial Y Velocity of Ball
	int x; //Current X Position of Ball
	int y; //Current Y Position of Ball
	static const int image_width = 62; //Paddleball's width
	static const int image_height = 100; //Paddleball's height
	static const int screen_width = 800; //Screen Width
	static const int screen_height = 500; //Screen Height
};

//[19.4] Multiple Inheritance
class RandomBall : virtual public Ball
{
public:
	RandomBall(); //Constructs a Random Ball
	virtual void BallBounce(int& player1, int& player2); //Changes direction of ball hits a paddle (velocity & acceleration changed)
	virtual void BallMove(int& player1, int& player2); //Moves ball position
	virtual ~RandomBall() {}; //Destructs the ball virtually
};

//[19.4] Multiple Inheritance
//[19.5] Virtual Inheritance
class InfluenceBall : virtual public Ball
{
public:
	InfluenceBall(); //Constructs an Influence Ball
	void IncreaseSpeed1(); //For Player 1: Increases Speed of ball heading towards Player 2
	void IncreaseSpeed2(); //For Player 2: Increases Speed of ball heading towards Player 1
	void DecreaseSpeed1(); //For Player 1: Decreases Speed of ball heading towards Player 2
	void DecreaseSpeed2(); //For Player 2: Decreases Speed of ball heading towards Player 1
	virtual void BallBounce(int& player1, int& player2); //Changes direction of ball hits a paddle (velocity & acceleration constant)
	virtual void BallMove(int& player1, int& player2); //Moves ball position
	virtual ~InfluenceBall() {}; //Destructs the ball virtually
};

//[19.4] Multiple Inheritance
//[19.5] Virtual Inheritance
class RandomInfluenceBall : public RandomBall, public InfluenceBall
{
public:
	RandomInfluenceBall(); //Constructor
	virtual void BallBounce(int& player1, int& player2); //Changes direction of ball hits a paddle (velocity & acceleration changed)
	virtual void BallMove(int& player1, int& player2); //Moves ball position
};

#endif