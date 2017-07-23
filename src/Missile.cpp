/*
 * Missile.cpp
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#include "Missile.h"
#include "Entity.h"
#include "GeoMaths.h"

#include <iostream>

float missileSpeed = 20.0f;

Missile::Missile(sf::Vector2f startPos, float direction) : Entity(), range(30) {
    angle = direction;
    myTextureLocation += "Missile.png";
    velocity = GeoMaths::rotateVector(velocity, angle)*missileSpeed;
    type = EntityType::Missile;

    setupSprite(startPos);
}

Missile::~Missile() {

}

void Missile::tick(int delta) {
    range -= delta;

    if(range < 0) {
        alive = false;
    }

    Entity::tick(delta);
}
