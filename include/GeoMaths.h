/*
 * GeoMaths.h
 *
 *  Created on: 4 May 2015
 *      Author: David
 */

#ifndef GEOMATHS_H_
#define GEOMATHS_H_

#include <SFML/Graphics.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class GeoMaths {
public:
	GeoMaths();
	virtual ~GeoMaths();
	static float distanceBetweenPoints(sf::Vector2f, sf::Vector2f);
	static sf::Vector2f rotateVector(sf::Vector2f, float);
};

#endif /* GEOMATHS_H_ */
