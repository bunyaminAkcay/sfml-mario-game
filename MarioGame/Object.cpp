#include "Object.h"
#include <SFML/Graphics.hpp>

//class abstract olmali

Object::Object(sf::RenderWindow* window) {//constructor
	this->heading = 0;
	this->speed = 0;
	this->state = 0;
	this->window = window;
	sf::Vector2f initialPosition;
	initialPosition = sf::Vector2f(0, 0);
	this->pos = initialPosition;
}

void Object::setPosition(sf::Vector2f pos){ //Sets position of the object
	this->sprite.setPosition(pos);
	this->pos = pos;
}

sf::Vector2f Object::getPosition() { //Gets position of the object
	return this->pos;
}

void Object::draw(sf::RenderWindow& window) {//Draws current the object texture to screen
	window.draw(this->sprite);
}
