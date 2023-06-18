#include "Mario.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Game.h"

Mario::Mario(sf::RenderWindow* window) : Object::Object(window) {//Constructor
	this->marioRunning = false;//if mario running, it is true
	this->speed = 8;
	this->window = window;
	this->heading = -1;// heading = -1 because mario image in starting looking left, heading = 1 right
	this->vx = 0;
	this->vy = 0;
	for (int i = 0; i < 7; i++) {
		std::string fileName;
		sf::Texture texture;
		fileName = "assets/mario" + std::to_string(i+1) + ".png";
		if (!texture.loadFromFile(fileName)) {//upload mario images
			printf("Error while uploading mario image");// Handle an error.
		}
		this->textures[i] = texture;//set textures
	}
	this->state = 0;// state 0 for standing
	sf::Sprite sprite;
	sprite.setTexture(this->textures[0]);// textures[0] standing
	this->sprite = sprite;
	this->sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);//set sprote origin to its center
	this->setPosition(sf::Vector2f(512, 700));//mario starting position
};

void Mario::move(){ //Moves Mario left or right
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		marioRunning = true;//if pressed left, mario running
		this->vx = -this->speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		marioRunning = true;//if pressed right, mario running
		this->vx = this->speed;
	}
	else {
		marioRunning = false;//if not pressed right or left, mario is not running
		this->vx = (float)(this->vx * 0.9); //drop velocity gradually for smooth stop
		if (this->vx < 1 and this->vx > -1){// if abs(vx) < 1 => vx = 0
			this->vx = 0;
		}
	}
	//move animations
	if (this->state == 6) { // if mario is dead, 
		this->sprite.setTexture(this->textures[6]);//set mario fall texture
	}
	else if (this->state != 0 and this->vx == 0 and this->vy == 0) {//stand
		this->state = 0;
		this->sprite.setTexture(this->textures[0]);// set mario stand texture
	}
	else if (this->vx != 0 and this->vy == 0) {//mario is running
		if (marioRunning) {
			this->state = 1;
			int i = (this->animationClock.getElapsedTime().asMilliseconds() / 150);
			if (i > 2) {
				this->animationClock.restart();
			}
			else {
				this->sprite.setTexture(this->textures[i + 1]);
			}
		}
		else {//if mario is not running anymore. if there is no vy but there is vx, Mario is sliding
			this->state = 4;//sliding state
			this->sprite.setTexture(this->textures[4]);//set sliding texture
		}
	}
	else if (this->state != 2 and this->vy != 0) {//jump
		this->state = 2;//jump state
		this->sprite.setTexture(this->textures[5]);//set jump texture
	}
	//set heading
	if (this->vx > 0) {
		if (this->heading != 1) {
			this->sprite.scale(-1.f, 1.f);//flip sprite
			this->heading = 1;//if vx>0, heading should be 1, if not set to 1
		}
	}
	else if (this->vx < 0) {
		if (this->heading != -1) {
			this->sprite.scale(-1.f, 1.f);//flip sprite
			this->heading = -1;//if vx<0, heading should be -1, if not set to -1
		}
	}
}

void Mario::jump(bool down) { //Makes Mario jump (if down is true, Mario jumps down off the edge of a floor, otherwise he jumps up)
	if (!down){
		this->vy = -14;
	}
	else {
		this->vy = 14;
	}
};

void Mario::fall(void) { //Makes Mario fall straight down when he dies
	this->state = 6; //died
};