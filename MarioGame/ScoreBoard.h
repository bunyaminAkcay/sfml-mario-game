#pragma once
#include <string>


class ScoreBoard{

public:
	
	void setScore(int score); //Sets the score
	void setLives(int lives); //Sets the remaining lives
	int getLives(void); //Gets the remaining lives
	int getScore(void); // get score
	std::string getScoreAsString(); //get score as string

private:
	int score; //Current score
	int lives; //Remaining life count for Mario
	
};
