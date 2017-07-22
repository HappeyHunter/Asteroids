/*
 * Ship.h
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "Entity.h"

class Ship: public Entity {
public:
	Ship();
	virtual ~Ship();
	virtual void tick(int);
	void accelerate();
	void deccelerate();
	void turnLeft();
	void turnRight();
	int respawnShip(sf::Vector2f);

private:
	sf::Vector2f getNosePos();
	void createShip(sf::Vector2f);
	void turn(int);
    void passiveDecceleration(int);
};

#endif /* SHIP_H_ */
