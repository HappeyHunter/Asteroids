/*
 * Entity.cpp
 *
 *  Created on: 3 May 2015
 *      Author: David
 */

#include "Entity.h"
#include "MainWindow.h"
#include <math.h>
#include "GeoMaths.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

Entity::Entity() : velocity(1.0f,0.0f), type(EntityType::Unknown), alive(true)  {

}

Entity::~Entity() {
}

void Entity::tick(int delta) {    
    std::cout << getType() << " is alive: " << isAlive() << std::endl;
    
    updatePosition(delta);
}

sf::Sprite& Entity::getSprite() {
	return mySprite;
}

void Entity::setTexture(sf::Texture newTexture){
	myTexture = newTexture;
}

float Entity::getVelocityX() {
	return velocity.x;
}

float Entity::getVelocityY() {
	return velocity.y;
}


void Entity::updatePosition(int)
{
	float distanceX = getVelocityX();
	float distanceY = getVelocityY();

	checkWrapAround();

	mySprite.move(distanceX, distanceY);
}

void Entity::setAngle(float newAngle) {
	angle = newAngle;
}

float Entity::getAngle() {
	return angle;
}

void Entity::checkWrapAround() {
	float xValue = mySprite.getPosition().x;
	float yValue = mySprite.getPosition().y;

	if(yValue>MainWindow::gameHeight+getCollisionRadius()) {
		yValue = 0-getCollisionRadius();
	} else if(yValue<0-getCollisionRadius()) {
		yValue = MainWindow::gameHeight+getCollisionRadius();
	}

	if(xValue>MainWindow::gameWidth+getCollisionRadius()) {
		xValue = 0-getCollisionRadius();
	} else if(xValue<0-getCollisionRadius()) {
		xValue = MainWindow::gameWidth+getCollisionRadius();
	}

	mySprite.setPosition(xValue, yValue);
}

float Entity::getCollisionRadius() {
	return mySprite.getTextureRect().width/2;
}

void Entity::setupSprite(sf::Vector2f startPos) {

	if(myTexture.getSize().x == 0) {
		myTexture.loadFromFile(myTextureLocation);
	}

	mySprite.setTexture(myTexture);
	mySprite.setOrigin(myTexture.getSize().x/2, myTexture.getSize().y/2);
	mySprite.setPosition(startPos.x,startPos.y);
}

sf::Vector2f Entity::getPosition() {
	return mySprite.getPosition();
}

void Entity::destroyed() {
	alive = false;
}

bool Entity::isAlive() {
	return alive;
}

Entity::EntityType Entity::getType() {
	return type;
}
    
