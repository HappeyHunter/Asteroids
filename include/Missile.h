/*
 * Missile.h
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#ifndef MISSILE_H_
#define MISSILE_H_

#include "Entity.h"

class Missile: public Entity {
public:
	Missile(sf::Vector2f, float);
	virtual ~Missile();
	virtual void tick(int);
	bool updatePosition();
private:
	float range;
};

#endif /* MISSILE_H_ */
