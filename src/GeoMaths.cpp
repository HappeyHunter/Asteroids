/*
 * GeoMaths.cpp
 *
 *  Created on: 4 May 2015
 *      Author: David
 */

#include "GeoMaths.h"
#include <math.h>

GeoMaths::GeoMaths() {
	

}

GeoMaths::~GeoMaths() {
	
}

float GeoMaths::distanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt( pow((p2.x - p1.x),2) + pow((p2.y - p1.y), 2));
}

sf::Vector2f GeoMaths::rotateVector(sf::Vector2f vect, float direction) {
    float dirRads = direction*M_PI/180;
    float cosDir = cos(dirRads);
    float sinDir = sin(dirRads);
    
    return sf::Vector2f {vect.x*cosDir - vect.y*sinDir, vect.x*sinDir + vect.y*cosDir};
}
