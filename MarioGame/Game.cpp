#include "Object.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>

Game::Game(Mario* mario, Turtle** turtles, ScoreBoard* scoreBoard) {//constuctor
	this->mario = mario;
	this->turtles = turtles;
	this->scoreBoard = scoreBoard;
	pipeSprite[0].scale(-1.f, 1.f); //flip sprite
	pipeSSprite[1].scale(-1.f, 1.f); //flip sprite
}

void Game::drawBackground(sf::RenderWindow* window){ //Draws the background objects
	sf::Font font;

	if (!font.loadFromFile("assets/font.ttf")) {//uploading font
		printf("While uploading font.\n");
	}

	if (this->state == 0) {// for state = 0, game did not start
		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;
		if (!backgroundTexture.loadFromFile("assets/mariobackground2.jpg")) {//uploading background
			printf("Error while uploading image");// Handle an error.
		}
		else {//if there is not error display background
			backgroundSprite.setTexture(backgroundTexture);
			window->draw(backgroundSprite);
		}

		//mario text
		sf::Text text1, text2, text3;
		text1.setFont(font);
		text1.setString("MARIO");
		text1.setCharacterSize(250);
		text1.setPosition(70, 20);
		text1.setOutlineColor(sf::Color(0, 0, 0, 128));
		text1.setOutlineThickness(6);

		//by hebun++ text
		text2.setFont(font);
		text2.setString("by Hebun++");
		text2.setCharacterSize(50);
		text2.setFillColor(sf::Color::Red);
		text2.setPosition(355, 280);
		text2.setOutlineColor(sf::Color(0, 0, 0, 128));
		text2.setOutlineThickness(3);

		//press enter text
		text3.setFont(font);
		text3.setString("press enter to start");
		text3.setCharacterSize(45);
		text3.setPosition(190, 550);
		text3.setOutlineColor(sf::Color(0, 0, 0, 128));
		text3.setOutlineThickness(3);

		//draw texts
		window->draw(text1);
		window->draw(text2);
		window->draw(text3);
	}
	if (this->state == 1) {// for state = 1, game is running
		//define textures
		sf::Texture floorTexture;
		sf::Texture brickFloorTextures;
		sf::Texture pipeSTexture;
		sf::Texture pipeTexture;
		sf::Texture marioHeadTexture;
		//upload floor image
		if (!floorTexture.loadFromFile("assets/floor.png")) {
			printf("Error while uploading image");// Handle an error.
		}
		//upload brick image
		if (!brickFloorTextures.loadFromFile("assets/brick.png")) {
			printf("Error while uploading image");// Handle an error.
		}
		//upload s type pipe image
		if (!pipeSTexture.loadFromFile("assets/pipeS.png")) {
			printf("Error while uploading image");// Handle an error.
		}
		//upload pipe image
		if (!pipeTexture.loadFromFile("assets/pipe.png")) {
			printf("Error while uploading image");// Handle an error.
		}
		//upload mario head image
		if (!marioHeadTexture.loadFromFile("assets/mariohead.png")) {
			printf("Error while uploading image");// Handle an error.
		}
		//brickFloorLocations stores data of sprite locations and brick amount
		int brickFloorLocations[7][3] = { {0,285,14} ,{604,285, 14},{0, 510, 4},{904,510, 4},{272,480,16},{0,670,12}, {664,670,12} };
		brickFloorTextures.setRepeated(true); // repeat brick to crate floor
		for (int i = 0; i < 7; i++) {//upload all brick floors with for loop
			brickFloorSprites[i].setTextureRect(sf::IntRect(0, 0, 30 * brickFloorLocations[i][2], 34));
			brickFloorSprites[i].setTexture(brickFloorTextures);
			brickFloorSprites[i].setPosition(sf::Vector2f((float)brickFloorLocations[i][0], (float)brickFloorLocations[i][1]));
			window->draw(brickFloorSprites[i]);
		}
		//set floor sprite
		floorSprite.setTexture(floorTexture);
		floorSprite.setPosition(sf::Vector2f(0.f, 869.f));
		//set right pipe sprite
		pipeSprite[0].setTexture(pipeTexture);
		pipeSprite[0].setPosition(sf::Vector2f(130.f, 800.f));
		//set right s type pipe sprite
		pipeSSprite[0].setTexture(pipeSTexture);
		pipeSSprite[0].setPosition(sf::Vector2f(0.f, 130.f));
		//set left pipe sprite
		pipeSprite[1].setTexture(pipeTexture);
		pipeSprite[1].setPosition(sf::Vector2f(896.f, 800.f));
		//set left s type pipe sprite
		pipeSSprite[1].setTexture(pipeSTexture);
		pipeSSprite[1].setPosition(sf::Vector2f(1024.f, 130.f));
		//set unvisible walls sprite
		unvisibleWalls[0].setTextureRect(sf::IntRect(0, 0, 100, 1524));
		unvisibleWalls[0].setPosition(sf::Vector2f(-100, -500.f));
		//set unvisible walls sprite
		unvisibleWalls[1].setTextureRect(sf::IntRect(0, 0, 100, 1524));
		unvisibleWalls[1].setPosition(sf::Vector2f(1024, -500.f));
		//unvisibleFloorData stores unvisible floor sizes and positions
		int unvisibleFloorsData[6][4] = { {194, 10, 0, 202},{194, 10, 0, 125},{194, 10, 830, 202},{194, 10, 830, 125}, {130,10,0,785}, {130, 10, 894, 785} };
		for (int i = 0; i < 6; i++) {//for loop to set all unvisible sprites at once
			unvisibleFloors[i].setTextureRect(sf::IntRect(0, 0, unvisibleFloorsData[i][0], unvisibleFloorsData[i][1]));
			unvisibleFloors[i].setPosition(sf::Vector2f((float)unvisibleFloorsData[i][2], (float)unvisibleFloorsData[i][3]));
		}
		//Score text
		sf::Text text;
		text.setFont(font);
		text.setString(this->scoreBoard->getScoreAsString());
		text.setCharacterSize(80);
		text.setPosition(50, 5);
		//set mario head sprites that amount of mario lives - 1
		for (int i = 0; i < this->scoreBoard->getLives() - 1; i++) {
			sf::Sprite marioHeadSprite;
			marioHeadSprite.setTexture(marioHeadTexture);
			marioHeadSprite.setPosition((float)(400 + 50 * i), 55);
			window->draw(marioHeadSprite);
		}
		//draw all sprites
		window->draw(floorSprite);
		window->draw(pipeSprite[0]);
		window->draw(pipeSSprite[0]);
		window->draw(pipeSprite[1]);
		window->draw(pipeSSprite[1]);
		window->draw(text);
	}
	if (this->state == 2){//if state = 2, game is over
		//define bavkground texture and sprite
		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;
		sf::Text text1, text2, text3;
		//load background image
		if (!backgroundTexture.loadFromFile("assets/mariobackground3.jpg")) {
			//if background image did not upload 
			printf("Error while uploading image");//error message
			//background image include gameover text, if background didnt upload write game over text
			text1.setFont(font);
			text1.setString("Game over");
			text1.setCharacterSize(125);
			sf::FloatRect bounds1 = text1.getLocalBounds();
			text1.setPosition(512 - bounds1.width/2, 120);
			text1.setOutlineColor(sf::Color(0, 0, 0, 128));
			text1.setOutlineThickness(6);
			window->draw(text1);
		}
		else {// if background image uploaded successfully, draw background
			backgroundSprite.setTexture(backgroundTexture);
			window->draw(backgroundSprite);
		}
		//score text
		text2.setFont(font);
		text2.setString("score:"+std::to_string(this->scoreBoard->getScore()));
		text2.setCharacterSize(80);
		sf::FloatRect bounds2 = text2.getLocalBounds();
		text2.setPosition(512 - bounds2.width/2, 400);
		text2.setOutlineColor(sf::Color(0, 0, 0, 128));
		text2.setOutlineThickness(3);
		//restart text
		text3.setFont(font);
		text3.setString("Press enter to restart");
		text3.setCharacterSize(55);
		sf::FloatRect bounds3 = text3.getLocalBounds();
		text3.setPosition(512 - bounds3.width / 2, 530);
		text3.setOutlineColor(sf::Color(0, 0, 0, 128));
		text3.setOutlineThickness(3);
		//draw texts
		window->draw(text2);
		window->draw(text3);
	}
	if (this->state == 3){//for state = 3, game is won.
		//define background sprite
		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;
		//load background image
		if (!backgroundTexture.loadFromFile("assets/mariobackground.png")) {
			printf("Error while uploading image");// Handle an error.
		}
		else {
			//if background load successfully, draw background
			backgroundSprite.setTexture(backgroundTexture);
			window->draw(backgroundSprite);
		}
		//you win text
		sf::Text text1, text2, text3;
		text1.setFont(font);
		text1.setString("You win!");
		text1.setCharacterSize(150);
		sf::FloatRect bounds1 = text1.getLocalBounds();
		text1.setPosition(512 - bounds1.width / 2, 120);
		text1.setOutlineColor(sf::Color(0, 0, 0, 128));
		text1.setOutlineThickness(6);
		//score text
		text2.setFont(font);
		text2.setString("score:" + std::to_string(this->scoreBoard->getScore()));
		text2.setCharacterSize(80);
		sf::FloatRect bounds2 = text2.getLocalBounds();
		text2.setPosition(512 - bounds2.width / 2, 400);
		text2.setOutlineColor(sf::Color(0, 0, 0, 128));
		text2.setOutlineThickness(3);
		//press enter text
		text3.setFont(font);
		text3.setString("Press enter to restart");
		text3.setCharacterSize(55);
		sf::FloatRect bounds3 = text3.getLocalBounds();
		text3.setPosition(512 - bounds3.width / 2, 650);
		text3.setOutlineColor(sf::Color(0, 0, 0, 128));
		text3.setOutlineThickness(3);
		//draw texts
		window->draw(text1);
		window->draw(text2);
		window->draw(text3);
	}
}

bool Game::onFloor(Object* obj){ //Checks if object is touching a floor surface
	bool onFloor = false;
	sf::Sprite s;
	obj->sprite.setPosition(obj->sprite.getPosition()+ sf::Vector2f(0,1)); //set object position to 1 point lower so intersections can check
	for (int i = 0; i < 8; i++){
		//s sprite changes by i. 8 floor checked 
		if (i == 7) {
			s = floorSprite;
		}
		else {
			s = brickFloorSprites[i];
		}
		//if any floor and object has an intersect, set onfloor true
		if (obj->sprite.getGlobalBounds().intersects(s.getGlobalBounds())){
			onFloor = true;
			break; //touch detected so break loop
		}
	}
	obj->sprite.setPosition(obj->sprite.getPosition() - sf::Vector2f(0, 1)); //set back object position
	return (onFloor);
}

bool Game::checkAllCollision(Object *obj) {//check any collision 
	bool collision = false;
	sf::Sprite s;
	for (int i = 0; i < 21; i++) {
		//s sprite changes by i
		if (i == 8 or i == 9) {
			s = unvisibleWalls[i - 8];
		}
		else if (i == 7) {
			s = floorSprite;
		}
		else if (i >= 10 and i <= 15) {
			s = this->unvisibleFloors[i-10];
		}
		//this part is for turtle to turtle collision detection
		else if (i > 15 and i <21 and obj != this->turtles[i - 16]) {//checkAllCollision return true without obj != this->turtles[i - 16] because turtle crash itself
			for (int j = 0; j < 5; j++) {
				if (this->turtles[j] == obj) {//if obj is turtle, s = turtle else s = null. If s = null, any collision can not detect. So this part is only for turtle turtle collisions
					s = this->turtles[i - 16]->sprite;
				}
			}
		}
		else {// i = 0 to 8
			s = brickFloorSprites[i];
		}
		//check if there any collision
		if (obj->sprite.getGlobalBounds().intersects(s.getGlobalBounds())){			
			collision = true;
			break;
		}
	}
	return collision;
}

bool Game::checkWallCollision(Object* obj) {//check only wall collisions. This function provides to change turtles direction.
	bool collision = false;
	sf::Sprite s;
	for (int i = 0; i < 7; i++) {
		//chane s sprites with for loop
		if (i < 2 ) {
			s = unvisibleWalls[i];
		}
		else if ( i < 7 and obj != this->turtles[i - 2]) {
			s = this->turtles[i-2]->sprite;
		}
		//check if there is any intersects
		if (obj->sprite.getGlobalBounds().intersects(s.getGlobalBounds())){
			collision = true;
			break;//detected collision. break loop
		}
	}
	return collision;
}

bool Game::checkCollusion(Turtle* turtle, Mario* mario, int& side) {//Checks if Mario has hit a turtle and from which side
	if (mario->state != 6 and turtle->state != 6) {//if mario and turtle is alive
		if (mario->sprite.getGlobalBounds().intersects(turtle->sprite.getGlobalBounds())) {//if they intersect
			//dy is intersection height on y-axis.
			int dy = (int)(mario->sprite.getGlobalBounds().top + mario->sprite.getGlobalBounds().height - turtle->sprite.getGlobalBounds().top);
			int turtleHeadSize = 30;
			if (dy < turtleHeadSize) {//if dy > turtleHeadSize, mario touch the head
				side = 1; //mario on the turtle
				return true; //there is collision
			}
			else {// else mario touch the turtle body
				side = 2; //Mario next to the turtle
				return true; //there is collision
			}
		}
		else {
			side = 0; //no collision
			return false;
		}
	}
}