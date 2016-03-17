#include <allegro.h>
//#include <iostream>
#include <map> //so we can store the same name (if they have different high scores) twice
#include <utility>
#include <string>
#include "highscores.h"

//[15.3] Constructors 
myscores::HighScores::HighScores()
{
}

void myscores::HighScores::add_entry(int score, std::string name)
{
	score_map.insert(make_pair(score,name)); //add entry to multimap score_map
}

//[14.3] Input/Output
std::ostream& myscores::operator<<(std::ostream& out, myscores::HighScores& value)
{
	HighScoresIterator check;
	check.HSbegin(value); //iterator points to the first element
	//check.HSnext(); //iterate to next to avoid outputting NULL, in case it tries to point to NULL, but right now it doesn't, so it's commented out

	HighScoresIterator end;
	end.HSend(value); //iterator points to the last element, so we can compare it with the check.pos in the while loop below

	while(check.pos != end.pos) //if the check.pos does not point to NULL, which is the end of multimap, we can output
	{
		if(check.pos != value.score_map.end()) //if iterator doesn't point to NULL, we can use out <<
			out << check.get_first() << " " << check.get_second() << std::endl; //get_first gets the score, get_second gets the name
		check.HSnext(); //iterate to next element of multimap
	}
	return out;
}

//[14.3] Input/Output
//NOTE: THE CODE BELOW WOULD BE EASIER AND MORE EFFICIENT, BUT FOR THE SAKE OF THIS CLASS
//I USED THE CODE ABOVE TO PRACTICE WITH PRIVATE INHERITANCE AND FRIEND CLASSES

//std::ostream& myscores::operator<<(std::ostream& out, myscores::HighScores& value)
//{
//	std::multimap<std::string,int>::iterator pos;
//	for(pos = value.score_map.begin(); pos != value.score_map.end(); pos++)
//		out << pos->first << " " << pos->second << std::endl;
//	return out;
//}