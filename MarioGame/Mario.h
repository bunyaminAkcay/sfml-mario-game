#pragma once
#include "Object.h"

class Mario : public Object{

private:
	bool marioRunning;
public:
	float vx; //Horizontal speed
	float vy; //Vertical speed


	Mario(sf::RenderWindow* window); //Constructor
	void move(); //Moves Mario left or right
	void jump(bool down); //Makes Mario jump (if down is true, Mario jumps down off the edge of a floor, otherwise he jumps up)
	void fall(void); //Makes Mario fall straight down when he dies
};