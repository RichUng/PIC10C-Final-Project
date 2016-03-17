#ifndef _HIGHSCORES
#define _HIGHSCORES

#include <allegro.h>
#include <iostream>
#include <map> //so we can store the same name (if they have different high scores) twice
#include <utility>
#include <string>

//[18.7] Namespaces 
namespace myscores
{
	class HighScores
	{
	public:
		//[20.5] Associative Containers
		std::multimap<int, std::string> score_map;
		HighScores(); //default constructor
		void add_entry(int score, std::string); //adds a name/score pair
	
	//[18.4] Friends 
	friend class HighScoresIterator;
	friend std::ostream& operator<<(std::ostream& out, myscores::HighScores& value); //this line is needed if score_map is a private variable
	};

	//[18.6] Private Inheritance
	class HighScoresIterator : private std::multimap<int, std::string>
	{
	public:
		//[20.2] Iterators
		std::multimap<int, std::string>::iterator pos; //use the std::multimap iterator

		std::multimap<int, std::string>::iterator* HSbegin(HighScores& temp)
		{
			pos = temp.score_map.begin(); //sets the temp score_map multimap iterator to begin
			return &pos;
		}
		std::multimap<int, std::string>::iterator* HSend(HighScores& temp)
		{
			pos = temp.score_map.end(); //sets the temp score_map multimap iterator to end
			return &pos;
		}
		void HSnext()
		{
			pos++; //increment the iterator
		}
		bool equals(std::multimap<int, std::string>::iterator right) const
		{
			return pos == right; //compares two iterators and returns true if both point to the same memory
		}
		int get_first()
		{
			return pos->first; //returns the string (first) of an element
		}
		std::string get_second()
		{
			return pos->second; //returns the integer (second) of an element
		}
	friend std::ostream& operator<<(std::ostream& out, myscores::HighScores& value); //if pos is a private member variable, we need to friend it
	};
}

#endif