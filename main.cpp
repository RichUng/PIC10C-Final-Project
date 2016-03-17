//[19.6] Software Frameworks
#include <allegro.h>
#include <winalleg.h> //so we can use fstream
//These are third party software frameworks that we used and improved
//to help make our own program! =]

#include <fstream>
#include <string>
#include <stdexcept>
#include "ball.h"
#include "inventory.h"
#include "highscores.h"
#include "selectscreen.h"
#include "gameover.h"
#include "paddlemove.h"
#include "checkwin.h"
#include "modes.h"
#include <ctime>
#include <time.h>
#include "obstacle.h"

//define the screenWidth and screenHeight for set_gfx_mode (the width and height of the game window)
#define screenWidth 800
#define screenHeight 500

//define the image width and image height
const int image_width = 62;
const int image_height = 100;

bool before_start = true; //if before_start is false, that means the user pressed a key to start the game
bool user_input = true; //if user_input is true, we will enter the high score screen
bool highscorecheck = false; //if highscorecheck is false, we will output high score name and score to file
bool continue_game = true; //if continue_game is false, that means a player has won already and the game is stopped
bool is_empty_string = true; //if is_empty_string is true, the user has entered an empty string and we do not output it to the file
bool keydown = false; //if keydown false, it prevents user from holding down the button
std::string letter_input = ""; //sets the letter to correspond to the mode
int player1score = 0; //Player 1's score
int player2score = 0; //Player 2's score

//timer routine to control speed of paddle movement
long time_count = 0;
void incr_timer(){time_count++;}
END_OF_FUNCTION(incr_timer);

//this function is used to use the "X" button to close the window
bool windowClose = false;
void CloseButtonCallBack()
{
	windowClose = true; //if the "X" is held down by the mouse, then windowClose is equal to true
}
END_OF_FUNCTION(CloseButtonCallBack()) //used at the end of a function for timing functions

//Ascii function to read user_input for the high score screen
void Ascii(std::string& name, int val)
{
	val = readkey() & 0xff;

	//if user presses enter, then loop back to select_screen
	if(val == 13)
	{
		if(name != "")
			is_empty_string = false;
		user_input = false;
		highscorecheck = true;
	}
	//if user enters the spacebar, then throw exception
	if(val == 32)
		throw std::invalid_argument("Invalid Argument!");
	//if user enters backspace, then delete the character that was just inputted
	if(val == 8)
	{
		name = name.substr(0, name.length()-1);
	}
	else
	{
		name += val; //concatenate string with val
	}
}

int main()
{
	allegro_init(); //initializes allegro, so that we can use their functions
	install_keyboard(); //sets up so that we can read in user keyboard input
	install_timer(); //frames per second (so that we can see the ball and paddles move
	set_color_depth(32); //sets the global pixel color depth
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenWidth, screenHeight, 0, 0); //a windowed mode of the game with 1100 * 700 pixels
	set_window_title("Ping Pong Game");

	LOCK_FUNCTION(incr_timer); 
	LOCK_VARIABLE(counter);

	LOCK_FUNCTION(CloseButtonCallBack()); //to avoid interupts
	LOCK_VARIABLE(windowClose);

	install_int_ex(incr_timer, BPS_TO_TIMER(60)); //used to start the timer routine at 60 frames per second
	set_close_button_callback(CloseButtonCallBack); //sets up the close "X" button so that when the user clicks "X", the program will exit and close

	//to set the high score
	std::string name = "";
	int name_val = 0;
	
	//if closeWindow is false, then continue to run program
	while(!windowClose)
	{
		user_input = true; //have to initialize user_input so that we can enter the high score again if needed
		//displays the welcome select screen
		BITMAP* select = create_bitmap(screenWidth, screenHeight);
		while(!windowClose && before_start == true && keydown == false)
		{
			select_screen(before_start,letter_input, keydown, select); //call the selection screen, which outputs the text layout and options
			blit(select, screen, 0, 0, 0, 0, screenWidth, screenHeight); //merges screen together
			continue_game = true;
			player1score = 0;
			player2score = 0;
			time_count = 0;
			clear_bitmap(select);
		}
		destroy_bitmap(select); //to avoid memory leaks

		//Once a key is pressed in the select screen, keydown becomes true
		//and exits the loop above, this is to reset it back to false for later use.
		keydown = false;

			//Position [0][0] and [1][0] = horizontal movement, which we don't need to manipulate
			//Position [0][1] and [1][1] = vertical movement, which we do need to manipulate
		int Position[2][2] = {0, screenHeight/2, screenWidth - image_height, screenHeight/2}; //screenWidth - 100 because the width of the image is 100 pixels wide
		int moveSpeed = 13; //the speed in which the paddle moves up and down
		BITMAP* Buffer = create_bitmap(screenWidth, screenHeight); //create buffer to prevent flickering of screen
		BITMAP* Player_1_image = load_bitmap("Player_1_image.bmp", NULL); //loads image to the bitmap
		BITMAP* Player_2_image = load_bitmap("Player_2_image.bmp", NULL); //loads image to the bitmap

		//Initializes start time of the game in startClock
		//and initializes finishClock time and other variables for later use.
		clock_t startClock = clock();
		clock_t finishClock;
		double timeCount = 0;
		double elapsedTime = 0;
		char clocker[10];

		//Initializes inventory of balls
		Inventory it;

		//game loop
		while(!windowClose && continue_game == true)
		{
			// Update Loop
			while(time_count > 0 && continue_game == true)
			{
				//Through the character select screen, letter_input equals a letter,
				//this makes letter_input set the mode and run the correct function
				//to allow the correct keyboard inputs.
				if(key[KEY_ESC])
					windowClose = true;
				if(letter_input == "A")
					ModeA(it);
				if(letter_input == "B")
					ModeB(it);
				if(letter_input == "C")
					ModeC(it);
				if(letter_input == "D")
					ModeD(it);
				if(letter_input == "E")
					ModeE(it, keydown);

				//Obstacle class lets you place obstacles on the field
				//Currently, it is located on point (300,100) with a box length of 200
				//First parameter determines what type of ball the obstacle has an effect on
				//Second parameter determines what player it will apply to
				//Note: If Second parameter is 0, it affects both players by randomly
				//teleporting the ball
				//Note: Obstacle boundaries are invisible!

				//Feel free to uncomment the next two lines and play around with the obstacle function
				//First Template Parameter Options: RandomBall, InfluenceBall, RandomInfluenceBall
				//Second Template Parameter Options: 0(teleport), 1(harms player 1), 2(harms player 2)
			//	Obstacle<RandomInfluenceBall,0> fun;
			//	fun.reflect(it);

				Paddle1Move(Position[0][1], moveSpeed); //pass in Position[0][1] to manipulate vertical paddle movement
				Paddle2Move(Position[1][1], moveSpeed); //pass in Position[1][1] to manipulate vertical paddle movement
				for(int i=0; i<it.get_size(); i++)
					it[i]->BallMove(Position[0][1], Position[1][1]); //Pass in ball & paddle locations to move ball
				CheckWin(it, player1score, player2score, continue_game); //Checks if ball is out of the screen to give a player a point.
				time_count--;
			}

			finishClock = clock(); //Records current time
			timeCount = difftime (finishClock, startClock); //Gets difference between start time and current time
			elapsedTime = (timeCount/1000); //Converts the time to seconds
			const int starttime = 20; //This integer determines how long the game can be played
			int timeleft = starttime - elapsedTime; //Gives the amount of time left for the game
			if (timeleft <= 0) //If time is up, continue_game is false and ends the game
				continue_game = false;
			textout_ex(Buffer, font, "Time left: ", 10, 10, makecol(100,100,100), makecol(0,0,0));
			textout_ex(Buffer, font, itoa(timeleft, clocker, 10), 100, 10, makecol(100,100,100), makecol(0,0,0)); //Displays time left

			//Used to convert the int "player1score" into a char* for the textout_ex function
			char score1[10];
			char score2[10];

			//[15.2.3] Array bounds errors
			if(player1score >= 1000000000)
				player1score = 0;
			if(player2score >= 1000000000)
				player2score = 0;
			//Just to make sure right?

			//Printout score
			textout_ex(Buffer, font, "Player 1 Score: ", (screenWidth/4), 10, makecol(100,100,100), makecol(0,0,0));
			textout_ex(Buffer, font, "Player 2 Score: ", (screenWidth/2), 10, makecol(100,100,100), makecol(0,0,0));
			textout_ex(Buffer, font, itoa(player1score, score1, 10), (screenWidth/4)+150, 10, makecol(100,100,100), makecol(0,0,0));
			textout_ex(Buffer, font, itoa(player2score, score2, 10), (screenWidth/2)+150, 10, makecol(100,100,100), makecol(0,0,0));
			//Note: itoa converts int to a char* and places it in a char array (in this case, score1 and score2)

			//Draw paddles
			draw_sprite(Buffer, Player_1_image, Position[0][0], Position[0][1]);
			draw_sprite(Buffer, Player_2_image, Position[1][0], Position[1][1]);
			for(int i=0; i<it.get_size(); i++)
				it[i]->draw(Buffer); //draws the ball into Buffer
			blit(Buffer, screen, 0, 0, 0, 0, screenWidth, screenHeight);
			if(continue_game == true)
				clear_bitmap(Buffer); //There's another clear_bitmap function for when the game is over
		}

		it.clear(); //destroys all balls

		if(!windowClose)
		{
			gameOver(player1score,player2score, Buffer);//display message after game is over
			blit(Buffer, screen, 0, 0, 0, 0, screenWidth, screenHeight);
			rest(1000);//when the game has stopped, rest 1 seconds
			clear_bitmap(Buffer);
		}

		clear_keybuf();//clears the keyboard buffer so we can receive user input

		//The following code is to initialize variables for high score input and output
		std::string temp = ""; //string temp is used to hold the name variable
		myscores::HighScores original_highscore; //creates a multimap
		std::string temp_name = "";
		int temp_score = 0; //temporary score to hold score
		int lowest_score = 0; //holds the lowest score, taken from input file
		std::string list_names = "High Scores:";
		std::multimap<int, std::string>::iterator pos; //initializes iterator for multimap

		//if user didn't press X button, and user_input is true, and players did not tie, then enter if statement
		if(!windowClose && user_input == true && player1score != player2score)
		{
			//input from file
			std::ifstream input_file;
			//[17.3] Exceptions
			try
			{
				input_file.open("highscore.txt"); //opens input file
				if(input_file.fail()) //if we cannot open the file (because it doesn't exist), throw exception
					throw std::invalid_argument("Invalid Argument!");
			}
			catch(std::invalid_argument& e) //catch invalid_argument exception
			{
				std::string what = e.what();
				std::string error = "The file that you are trying to open does not exist, please create a 'highscore.txt' in folder.";
				textout_centre_ex(Buffer, font, what.c_str(), screenWidth/2, 20, makecol(0,255,0), makecol(0,0,0));
				textout_centre_ex(Buffer, font, error.c_str(), screenWidth/2, 30, makecol(0,255,0), makecol(0,0,0));
				break;
			}

			//keep copying info from txt document until end of file, which will break the while loop
			while(true)
			{
				if(input_file.eof()) //if end of file, break while loop
					break;
				temp_name = ""; //string temp is used to hold the name variable
				temp_score = 0;
				input_file >> temp_score; //stores first variable into temp_score
				if(input_file.fail()) //if file is corrupt, break while loop
					break;
				input_file >> temp_name; //stores second variable into temp_name
				if(input_file.fail()) //if file is corrupt, break while loop
					break;
				if(temp_score <= lowest_score)
					lowest_score = temp_score; //sets lowest score to the lowest score from the input file
				original_highscore.add_entry(temp_score, temp_name); //adds entry to multimap
			}

			//erases the first elements of multimap scoremap until only the last 10 are left
			while(original_highscore.score_map.size() > 10)
			{
				pos = original_highscore.score_map.begin(); //iterator points to first element of multimap score_map
				original_highscore.score_map.erase(pos); //erase the element at position pos
			}
			pos = original_highscore.score_map.begin(); //set position pos to begin
			lowest_score = pos->first; //store the int of the first element into lowest_score
			input_file.close(); //close input file
		}

		//while user didnt press close button and user_input is true and either player 1 wins or player 2 wins and it's not a tie, enter high score screen
		while(!windowClose && user_input == true && (player1score > lowest_score || player2score > lowest_score) && player1score != player2score)
		{
			textout_centre_ex(Buffer, font, list_names.c_str(), screenWidth/2, screenHeight/8, makecol(100,100,100), makecol(0,0,0));
			
			pos = original_highscore.score_map.begin(); //pos points to first element of multimap score_map
			pos++; //start at the second element of map because first element is empty string and number of temp_score
			int i = 0;
			int j = 0;
			while(pos!= original_highscore.score_map.end() && i < original_highscore.score_map.size() && j < 10) //iterate through score_map and print it out
			{
				int score = pos->first;
				std::string original_name = pos->second;
				char char_score[10];
				std::string result = original_name + " " + itoa(score,char_score,10); //concatenates score and name so we can output to screen
				textout_ex(Buffer, font, result.c_str(), screenWidth/2 - 50, screenHeight/6+(i*10), makecol(100,100,100), makecol(0,0,0));
				pos++;
				i++;
				j++;
			}

			std::string ask_name = "You have received a high score! Please Enter Your Name: ";
			textout_centre_ex(Buffer, font, ask_name.c_str(), screenWidth/2, screenHeight/2 + 120, makecol(255,0,0), makecol(0,0,0));
			//[17.3] Exceptions
			try
			{
				while(keypressed() && is_empty_string) //allows user to input their name
				{
					Ascii(name, name_val); //calls Ascii function
					if(name.length() > 10) //if user types a name that is greater than 10 characters long, then throw a length_error exception
						throw std::length_error("Length Error!");
				}
			}
			catch(std::length_error& e) //catch the exception
			{
				std::string what = e.what();
				std::string error = what + " You entered too many characters! Please enter again."; //concatenate string variables
				textout_centre_ex(screen, font, error.c_str(), screenWidth/2, screenHeight/2 + 140, makecol(0,255,0), makecol(0,0,0)); //write it out to screen, not Buffer
				name = ""; //reinitialize name
				name_val = 0; //reinitialize name_val
				rest(1500); //rest for 1.5 sec before allowing user to type again
				clear_keybuf();	//clear keyboard buffer
				clear_bitmap(Buffer); //clear Buffer bitmap
			}
			catch(std::invalid_argument& e)
			{
				std::string what = e.what();
				std::string error = what + " You can't enter spaces! Please enter again.";
				textout_centre_ex(screen, font, error.c_str(), screenWidth/2, screenHeight/2 + 140, makecol(0,255,0), makecol(0,0,0)); //write it out to screen, not Buffer
				name = ""; //reinitialize name
				name_val = 0; //reinitialize name_val
				rest(1500); //rest for 1.5 sec before allowing user to type again
				clear_keybuf();	//clear keyboard buffer
				clear_bitmap(Buffer); //clear Buffer bitmap
			}
			textout_centre_ex(Buffer, font, "               ", screenWidth/2, screenHeight/2 + 130, makecol(0,255,0), makecol(0,0,0)); //covers backspaces
			textout_centre_ex(Buffer, font, name.c_str(), screenWidth/2, screenHeight/2 + 130, makecol(0,255,0), makecol(0,0,0)); //allows user input
			blit(Buffer, screen, 0, 0, 0, 0, screenWidth, screenHeight); //copies screen bitmap to Buffer bitmap
		}

		//if user doesn't enter a name, we do not store it, and we do not copy it to file, then restart to the select screen
		if(name == "")
		{
			name_val = 0;
			is_empty_string = true;
			before_start = true;
		}

		//if user enters a name and the scores are not tied, output the score and name to file, along with the scores from the original file
		if( highscorecheck && (is_empty_string == false) && player1score != player2score )
		{
			int winner_score = 0;
			if(player1score > player2score && player1score > lowest_score)
				winner_score = player1score; //sets winner_score as player 1's score
			else if(player2score > player1score && player2score > lowest_score)
				winner_score = player2score; //sets winner_score as player 2's score
			original_highscore.add_entry(winner_score, name); //add name and score to highscore map
			//output name to file
			std::ofstream output_file;
			output_file.open("highscore.txt"); //opens output file
			output_file << original_highscore; //outputs file, using overloaded output operator
			output_file.close(); //closes output file
			highscorecheck = false; //reinitializes highscorecheck to false
		}

		//if try/catch didn't run, then the code below will clear buffers and reinitialize
		clear_keybuf();

		//clear bitmap to have a black screen
		clear_bitmap(Buffer);
		clear_bitmap(screen);

		//to avoid memory leaks, we want to destroy to bitmap
		destroy_bitmap(Buffer);
		destroy_bitmap(Player_1_image);
		destroy_bitmap(Player_2_image);
		
		//reinitialize variables for next loop
		name = "";
		name_val = 0;
		before_start = true;
		is_empty_string = true;
		keydown = false;
	}

	clear_bitmap(screen); //clear bitmap
	clear_keybuf(); //clear keyboard buffer
	allegro_exit(); //to avoid memory leaks

	return 0;
}
END_OF_MAIN()