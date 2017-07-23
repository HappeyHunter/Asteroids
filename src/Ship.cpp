/*
 * Ship.cpp
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#include "Ship.h"
#include "Missile.h"
#include "GeoMaths.h"
#include "Constants.h"

#include <math.h>
#include <iostream>

float maxSpeed {-20.0f};
float deccelerationValue {0.01f};
float turnSpeed {5.0f};

int accelerateValue {0};
int turnDirection {0};

sf::Vector2f acceleration {-0.1f, 0.0f};

Ship::Ship() : Entity() {
    myTextureLocation += "Ship.png";
	type = EntityType::Ship;
    velocity *= 0.0f;
}

Ship::~Ship() {
}

void Ship::tick(int delta) {


    if(accelerateValue <= 0) {
        passiveDecceleration(delta);
    }

    if(accelerateValue > 0) {
        velocity += GeoMaths::rotateVector(acceleration, getAngle())*(float)delta;
        accelerateValue = 0;
    } else {
        passiveDecceleration(delta);
    }

    turn(delta);

    Entity::tick(delta);
}

void Ship::accelerate(){
	accelerateValue = 1;
}

void Ship::deccelerate(){
	accelerateValue = -1;
}

void Ship::passiveDecceleration(int delta) {

	if((fabs(getVelocityX()) + fabs(getVelocityY()))>deccelerationValue*delta){
		velocity *= 0.99f;
	} else {
		velocity *= 0.0f;
	}
}

void Ship::turn(int delta) {
	float turnValue = turnSpeed*delta*turnDirection;

	if(turnValue != 0) {
        setAngle(getAngle()+turnValue);
        mySprite.rotate(turnValue);
	}

	turnDirection = 0;
}

void Ship::turnLeft() {
    turnDirection = -1;
}

void Ship::turnRight() {
    turnDirection = 1;
}

sf::Vector2f Ship::getNosePos() {
	sf::Vector2f pos = mySprite.getPosition();

	pos.y = pos.y - (sin(angle*M_PI/180)*(getCollisionRadius()+2));
	pos.x = pos.x - (cos(angle*M_PI/180)*(getCollisionRadius()+2));

	return pos;
}

int Ship::respawnShip(sf::Vector2f startPos) {
    alive = true;
    
    if(mySprite.getTexture() == nullptr) {
        setupSprite(startPos);
    } else {
        mySprite.setRotation(0);
        mySprite.setPosition(startPos);
    }

	setAngle(90);
    velocity *= 0.0f;

	return 0;
}
