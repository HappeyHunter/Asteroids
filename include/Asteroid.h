/*
 * Asteroid.h
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Entity.h"

class Asteroid: public Entity {
public:
    enum Size { Large, Medium, Small };

public:
	Asteroid(Size, sf::Vector2f);
	virtual ~Asteroid();

	static const int spawnRadius = 0;

private:
    void setAttributes();
    void createAsteroid(sf::Vector2f);

private:
    Size mySize;
};

#endif /* ASTEROID_H_ */
