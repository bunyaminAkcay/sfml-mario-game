#pragma once
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"
#include "ScoreBoard.h"
	
class Game {

public:
	sf::Sprite floorSprite;
	sf::Sprite brickFloorSprites[7];
	sf::Sprite pipeSSprite[2];
	sf::Sprite pipeSprite[2];
	sf::Sprite unvisibleWalls[2]; //unvisible walls prevent to fall object to edge of the game
	sf::Sprite unvisibleFloors[6]; //unvisible floors is for pipes. There is 2 invisible floor for each pipe so turtle can pass through pipes
	Mario* mario;
	Turtle** turtles;
	ScoreBoard* scoreBoard;
	float gravity =  0.4f;
	int state = 0; // state = 0 => game is not started. state = 1 => game is running. state = 2 => game finished with win. state = 3 => game finished with game over.  
	
	Game(Mario* mario, Turtle** turtles, ScoreBoard* scoreboard);
	void drawBackground(sf::RenderWindow* window); //Draws the background objects
	bool onFloor(Object* obj); //Checks if object is touching a floor surface
	bool checkAllCollision(Object* obj); //checks if object is touching any surface
	bool checkWallCollision(Object* obj); //checks if object is touching any wall surface
	bool checkCollusion(Turtle* turtle, Mario* mario, int& side);//Checks if Mario has hit a turtle and from which side. return 0 for no colision and 1 for top collision and 2 for sides 
};