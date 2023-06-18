#include "ScoreBoard.h"

void ScoreBoard::setScore(int score){ //Sets the score
	this->score = score;
}

void ScoreBoard::setLives(int lives){ //Sets the remaining lives
	this->lives = lives;
}

int ScoreBoard::getLives(void){//Gets the remaining lives
	return this->lives;
}

int ScoreBoard::getScore(void) {//Gets the remaining lives
	return this->score;
}

std::string ScoreBoard::getScoreAsString() {//gets score as a string
	int i = this->score + 1000000;// for extra 0s presentation, add 1000000 
	std::string s = std::to_string(i);//convert to string
	return s.substr(1, 6);//remove first letter that is "1"
}