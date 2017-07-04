/*
 * Entity.h
 *
 *  Created on: 3 May 2015
 *      Author: David
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

class Entity {
public:
    enum EntityType { Unknown = -1, Asteroid, Ship, Missile };

public:
	Entity();
	virtual ~Entity();
	virtual void tick(int);
	float getSpeed();
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f);
	float getVelocityX();
	float getVelocityY();
	float getVelocityRotation();
	float getAngle();
	sf::Sprite& getSprite();
	void setVelocityRotation(float);
	void updatePosition(int);
	void setTexture(sf::Texture);
	void setAngle(float);
	sf::Vector2f getPosition();
	float getCollisionRadius();
	void destroyed();
	bool isAlive();
	EntityType getType();

protected:
	void setupSprite(sf::Vector2f);
	void checkWrapAround();

protected:
	sf::Sprite mySprite;
	float angle;
	sf::Vector2f velocity;
	float velocityRotation;
	std::string myTextureLocation;
	sf::Texture myTexture;
	EntityType type;
	bool alive;

};

#endif /* ENTITY_H_ */
