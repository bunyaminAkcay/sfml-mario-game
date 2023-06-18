#include "Turtle.h"
#include "Object.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <stdlib.h>


Turtle::Turtle(sf::RenderWindow* window, float spawnTime) : Object::Object(window) {//constructor
	this->speed = 2;
	this->window = window;
	this->spawnTime = spawnTime;
	this->spawned = false;
	this->vx = 0;
	this->vy = 0;
	this->heading = 1;
	for (int i = 0; i < 5; i++) {
		std::string fileName;
		sf::Texture texture;
		fileName = "assets/turtle" + std::to_string(i+1) + ".png";
		if (!texture.loadFromFile(fileName)) {//load turtle images
			printf("Error while uploading turtle image");// Handle an error.
		}
		this->textures[i] = texture;//set texture to texture array
	}
	this->state = 1;
	sf::Sprite sprite;
	sprite.setTexture(this->textures[0]);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);//set origin to center of sprite
	this->sprite = sprite;
	
}


void Turtle::move() { //Moves turtle left or right
	//move animation
	if (this->state != 6) {//if turtle is not dead
		int j = (this->animationClock.getElapsedTime().asMilliseconds() % 600) / 200;//j change 0, 1, 2 by time
		if (this->state == 3){//turtle rotating
			this->sprite.setTexture(this->textures[3]);//set texture to rotating image
			this->animationClock.restart();//restart clock
		}
		else if(this->animationClock.getElapsedTime().asMilliseconds() > 200) {// clock restarted when rotating. Wait 200ms to set running animation. This means 200ms rotating time
			this->sprite.setTexture(this->textures[j]);//change sprite's texture over time
		}
	}
	
	this->speed =  2 + speedTimeClock.getElapsedTime().asSeconds() / 10;//turtle speed increase by time
	int sign = 1;
	if (this->vx < 0) {
		sign = -1;
	}
	this->vx = this->speed * sign;//set velocity from speed

	//set heading
	if (this->spawned) {
		if (this->vx > 0) {
			if (this->heading != -1) {
				this->sprite.scale(-1.f, 1.f);
				this->heading = -1;
			}
		}
		else if (this->vx < 0) {
			if (this->heading != 1) {
				this->sprite.scale(-1.f, 1.f);
				this->heading = 1;
			}
		}
	}
}

void Turtle::jump(bool down) {//Makes turtle jump (if down is true, turtle jumps down off the edge of a floor.Down being false can be optionally used for fly animation of turtle when it is hit from underneath by Mario)
	//turtle dont jump because gravity do same thing.
}

void Turtle::fall(void) {//Makes turtle fall when it dies
	this->state = 6;//fall state
	this->sprite.setTexture(this->textures[4]);//fall texture
	this->vx = 0;
}