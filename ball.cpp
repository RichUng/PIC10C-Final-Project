#include "ball.h"

//[19.1] Class Inheritance Hierarchies
//[15.3] Constructors 
Ball::Ball()
{
	ballsize = 27;
	image = load_bitmap("ball.bmp", NULL);
	//Makes a value from 0-3, and depending on the value places the ball in
	//one of the four screen corners, and initializes the correct speed/acceleration
	int setting = rand() % 4;
	if (setting == 0)
	{
		x0 = 0;
		y0 = 0;
		ax = (rand() % (50))/100;
		ay = (rand() % (50))/100;
		v0x = (rand() % (10-3))+3;
		v0y = (rand() % (10-3))+3;
	}
	else if (setting == 1)
	{
		x0 = screen_width;
		y0 = 0;
		ax = -(rand() % (50))/100;
		ay = (rand() % (50))/100;
		v0x = -(rand() % (10-3))-3;
		v0y = (rand() % (10-3))+3;
	}
	else if (setting == 2)
	{
		x0 = 0;
		y0 = screen_height;
		ax = (rand() % (50))/100;
		ay = -(rand() % (50))/100;
		v0x = (rand() % (10-3))+3;
		v0y = -(rand() % (10-3))-3;
	}
	else
	{
		x0 = screen_width-ballsize;
		y0 = screen_height-ballsize;
		ax = -(rand() % (50))/100;
		ay = -(rand() % (50))/100;
		v0x = -(rand() % (10-3))-3;
		v0y = -(rand() % (10-3))-3;
	}
	t = 0;
	vx = v0x;
	vy = v0y;
	x = x0;
	y = y0;
};

const int Ball::get_x()
{
	return x;
}

const int Ball::get_y()
{
	return y;
}

void Ball::draw(BITMAP* Buffer)
{
	//Uses Allegro function to draw an image
	draw_sprite(Buffer, image, x, y);
}

Ball::Ball(const Ball& right)
{
	//Copys image over because this is a dynamically allocated pointer to an image
	*image = *right.image;
}

Ball& Ball::operator=(const Ball& right)
{
	//Copys image over because this is a dynamically allocated pointer to an image
	*image = *right.image;
	return *this;
}

//[15.4] Destructors 
Ball::~Ball()
{
	//Destroys image
	destroy_bitmap(image);
}

RandomBall::RandomBall()
{
}

void RandomBall::BallBounce(int& player1, int& player2)
{	
	int nextt = t+1;
	int nextx = x0+v0x*nextt+((ax*nextt*nextt)/2);
	double speed = (rand() % (10-3))+3;
	//Check if the ball hits the boundaries (4 sides). If so reset initial coordinates/change direction.
	//Note: the acceleration and velocity randomly change when hit
	if(y >= screen_height-ballsize)
	{
		ax = (rand() % (50))/100;
		ay = (rand() % (50))/100;
		t = 0;
		ay = abs(ay)*-1;
		v0y = abs(speed)*-1;
		y0 = y;
		x0 = x;
	}
	if(y <=0)
	{
		ax = (rand() % (50))/100;
		ay = (rand() % (50))/100;
		t = 0;
		ay = abs(ay);
		v0y = abs(speed);
		y0 = y;
		x0 = x;
	}
	if(y <= player1+(image_height/2) && y >= player1-(image_height/2) && x >= image_height && nextx <= image_height)
	{
		ax = (rand() % (50))/100;
		ay = (rand() % (50))/100;
		t = 0;
		ax = abs(ax);
		v0x = abs(speed);
		y0 = y;
		x0 = x;
	}
	if(y <= player2+(image_height/2) && y >= player2-(image_height/2) && x <= screen_width-ballsize-image_height && nextx >= screen_width-ballsize-image_height)
	{
		ax = (rand() % (50))/100;
		ay = (rand() % (50))/100;
		t = 0;
		ax = abs(ax)*-1;
		v0x = abs(speed)*-1;
		y0 = y;
		x0 = x;
	}
}

void RandomBall::BallMove(int& player1, int& player2)
{
	BallBounce(player1, player2);
	//Increment time
	++t;
	//Basic motion equations to find new position
	x = x0+v0x*t+((ax*t*t)/2);
	y = y0+v0y*t+((ay*t*t)/2);
}

InfluenceBall::InfluenceBall()
{
	//Loads a Pokeball image.
	image = load_bitmap("pokeball.bmp", NULL);
}

void InfluenceBall::IncreaseSpeed1()
{
	//If the ball is not too fast and is heading towards Player 2 this function will
	//make the ball go faster.
	if(v0x < 15 && v0x > 0)
	{
		vx = ax*t+v0x + 3;
		v0x = vx;
		t = 0;
		y0 = y;
		x0 = x;
	}
}

void InfluenceBall::IncreaseSpeed2()
{
	//If the ball is not too fast and is heading towards Player 1 this function will
	//make the ball go faster.
	if(v0x > -15 && v0x < 0)
	{
		vx = ax*t+v0x - 3;
		v0x = vx;
		t = 0;
		y0 = y;
		x0 = x;
	}
}

void InfluenceBall::DecreaseSpeed1()
{
	//If is heading towards Player 1 at a fast speed
	//this function will make the ball go slower.
	if(v0x < -3)
	{
		vx = ax*t+v0x + 3;
		v0x = vx;
		t = 0;
		y0 = y;
		x0 = x;
	}
}

void InfluenceBall::DecreaseSpeed2()
{
	//If is heading towards Player 2 at a fast speed
	//this function will make the ball go slower.
	if(v0x > 3)
	{
		vx = ax*t+v0x - 3;
		v0x = vx;
		t = 0;
		y0 = y;
		x0 = x;
	}
}

void InfluenceBall::BallBounce(int& player1, int& player2)
{	
	int nextt = t+1;
	int nextx = x0+v0x*nextt+((ax*nextt*nextt)/2);
	//Check if the ball hits the boundaries (4 sides). If so reset initial coordinates/change direction.
	//Note: the acceleration and velocity do not change when it hits the boundary.
	if(y >= screen_height-ballsize)
	{
		vy = ay*t+v0y;
		t = 0;
		ay = abs(ay)*-1;
		v0y = abs(vy)*-1;
		y0 = y;
		x0 = x;
	}
	if(y <=0)
	{
		vy = ay*t+v0y;
		t = 0;
		ay = abs(ay);
		v0y = abs(vy);
		y0 = y;
		x0 = x;
	}
	if(y <= player1+(image_height/2) && y >= player1-(image_height/2) && x >= image_height && nextx <= image_height)
	{
		vx = ax*t+v0x;
		t = 0;
		ax = abs(ax);
		v0x = abs(vx);
		y0 = y;
		x0 = x;
	}
	if(y <= player2+(image_height/2) && y >= player2-(image_height/2) && x <= screen_width-ballsize-image_height && nextx >= screen_width-ballsize-image_height)
	{
		vx = ax*t+v0x;
		t = 0;
		ax = abs(ax)*-1;
		v0x = abs(vx)*-1;
		y0 = y;
		x0 = x;
	}
}

void InfluenceBall::BallMove(int& player1, int& player2)
{
	BallBounce(player1, player2);
	//Increment time
	++t;
	//Basic motion equations to find new position
	x = x0+v0x*t+((ax*t*t)/2);
	y = y0+v0y*t+((ay*t*t)/2);
}

RandomInfluenceBall::RandomInfluenceBall()
{
	//Loads RandomInfluenceBall image
	image = load_bitmap("barbaro_ball.bmp", NULL);
}

void RandomInfluenceBall::BallBounce(int& player1, int& player2)
{
	//Runs either the RandomBall's ballbounce function or the InfluenceBall's ballbounce function. 50/50 chance
	if (0 == rand() % 2)
		RandomBall::BallBounce(player1,player2);
	else
		InfluenceBall::BallBounce(player1,player2);
}

void RandomInfluenceBall::BallMove(int& player1, int& player2)
{
	//Slowly increases acceleration as the ball moves.
	//So there's Jerk.
	if (ay<0)
		ay = ay-0.02;
	if (ay>0)
		ay = ay+0.02;
	if (ax<0)
		ax = ax-0.02;
	if (ax>0)
		ax = ax+0.02;
	InfluenceBall::BallMove(player1,player2);
}