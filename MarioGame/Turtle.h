#pragma once
#include "Object.h"

class Turtle : public virtual Object {

private:
	
public:
	float spawnTime; //turtle spawn time as seconds
	sf::Clock spawnTimeClock;
	sf::Clock speedTimeClock;
	bool spawned; // if turtle is spawned, spawned is true
	float vx; //Horizontal speed
	float vy; //Vertical speed
	bool dead = false; // if turtle is dead, dead is true

	Turtle(sf::RenderWindow* window, float spawnTime);//Constructor
	void move(); //Moves turtle left or right
	void jump(bool down); //Makes turtle jump (if down is true, turtle jumps down off the edge of a floor.Down being false can be optionally used for fly animation of turtle when it is hit from underneath by Mario)
	void fall(void); //Makes turtle fall when it dies
};