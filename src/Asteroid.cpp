/*
 * Asteroid.cpp
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#include "Asteroid.h"
#include "GeoMaths.h"

Asteroid::Asteroid(Size asteroidSize, sf::Vector2f startPos) : Entity(), mySize(asteroidSize) {
    type = EntityType::Asteroid;

    createAsteroid(startPos);
}

Asteroid::~Asteroid() {
}

void Asteroid::createAsteroid(sf::Vector2f startPos) {

    setAttributes();

	setupSprite(startPos);

	mySprite.setRotation(rand() % 360);
}

void Asteroid::setAttributes() {
    velocity.x = 1;
    velocity.y = 1;

    switch(mySize) {
        case Size::Large :
            myTextureLocation = "Resources/LargeAsteroid.png";
            velocity *= 0.5f;
            scoreValue = 20;
            break;
        case Size::Medium :
            myTextureLocation = "Resources/MediumAsteroid.png";
            velocity *= 1.0f;
            scoreValue = 50;
            break;
        case Size::Small :
            myTextureLocation = "Resources/SmallAsteroid.png";
            velocity *= 2.0f;
            scoreValue = 100;
            break;
    }    

    angle = rand() % 360;
    
    velocity = GeoMaths::rotateVector(velocity, angle);
}

Asteroid::Size Asteroid::getSize()
{
    return mySize;
}

