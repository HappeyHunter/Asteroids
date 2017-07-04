/*
 * MainWindow.cpp
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#define TICK 1

#include "MainWindow.h"
#include "Entity.h"
#include "Ship.h"
#include "Asteroid.h"
#include "GeoMaths.h"
#include "Missile.h"

#include <math.h>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

Ship shipEntity;

sf::Font aFont;
sf::Text scoreText("Score: ", aFont);

std::vector<std::unique_ptr<Asteroid>> asteroids;
std::vector<std::unique_ptr<Missile>> missiles;

bool reloading = false;

const int asteroidCount = 8;

int score = 0;

MainWindow::MainWindow() {
	shipCommands.resize(sf::Keyboard::KeyCount, false);
}

MainWindow::~MainWindow() {
	
}



int MainWindow::runGame() {
	// Setup window stuff
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Asteroids!");
	window.setFramerateLimit(60);
	srand(time(NULL));

	// Create world stuff
	createShip();
	createAsteroids();
	prepareScore();

    // Main loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				processKeyPress(event);
				break;
			case sf::Event::KeyReleased:
				processKeyRelease(event);
				break;
			default:
				break;
			}
		}

		executeShipCommands();
		gameTick();

		checkCollisions();
		updateScore();
		drawEntities(window);
	}

	return 0;
}

void MainWindow::gameTick() {
    // Remove dead things first


    // Asteroids
    unsigned int i = 0;
    while(i < asteroids.size()) {
		if(!asteroids[i]->isAlive()) {
            asteroids.erase(asteroids.begin()+i);
		} else {
            ++i;
		}
	}

	// Missiles
	i = 0;
    while(i < missiles.size()) {
		if(!missiles[i]->isAlive()) {
            missiles.erase(missiles.begin()+i);
		} else {
            ++i;
		}
	}

    // Now tick everything
    // Ship
    shipEntity.tick(TICK);

    // Asteroids
    for(unsigned int i = 0; i < asteroids.size(); i++) {
		asteroids[i]->tick(TICK);
	}

	// Missiles
	for(unsigned int i = 0; i < missiles.size(); i++) {
		missiles[i]->tick(TICK);
	}
}

int MainWindow::createShip() {

	sf::Vector2f startPos;

	startPos.x = gameWidth/2;
	startPos.y = gameHeight/2;

	shipEntity.respawnShip(startPos);

	return 0;
}

int MainWindow::createAsteroids() {

	for(int i = 0; i<asteroidCount; i++) {
		sf::Vector2f startPos;

		startPos.x = rand() % gameWidth;
		startPos.y = rand() % gameHeight;

		startPos.x = rand() % gameWidth;
		startPos.y = rand() % gameHeight;

		asteroids.emplace_back(new Asteroid(Asteroid::Large, startPos));
	}

	return 0;
}

void MainWindow::processKeyPress(sf::Event event) {
	if(event.key.code == sf::Keyboard::Space && !reloading) {
		missiles.emplace_back(new Missile(shipEntity.getPosition(), shipEntity.getAngle()+180));
        reloading = true;
	} else if(event.key.code == sf::Keyboard::BackSpace) {
		resetGame();
	} else if(event.key.code != sf::Keyboard::Unknown){
        shipCommands[event.key.code] = true;
	}
}

void MainWindow::processKeyRelease(sf::Event event) {
	if(event.key.code == sf::Keyboard::Space) {
		reloading = false;
	} else if(event.key.code != sf::Keyboard::Unknown){
		shipCommands[event.key.code] = false;
	}
}

void MainWindow::drawEntities(sf::RenderWindow& window) {
	window.clear();

	for(unsigned int i = 0; i < asteroids.size(); i++) {
		window.draw(asteroids[i]->getSprite());
	}

	for(unsigned int i = 0; i < missiles.size(); i++) {
		window.draw(missiles[i]->getSprite());
	}

	window.draw(shipEntity.getSprite());

	window.draw(scoreText);

	window.display();
}

void MainWindow::executeShipCommands() {
	if(shipCommands[sf::Keyboard::Up]) {
		shipEntity.accelerate();
	}
	if(shipCommands[sf::Keyboard::Down]) {
		shipEntity.deccelerate();
	}
	if(shipCommands[sf::Keyboard::Left]) {
		shipEntity.turnLeft();
	}
	if(shipCommands[sf::Keyboard::Right]) {
		shipEntity.turnRight();
	}
}

void MainWindow::checkCollisions() {
    // Check if the player hit an asteroid
    for(unsigned int i = 0; i < asteroids.size(); i++) {
        if(GeoMaths::distanceBetweenPoints(asteroids[i]->getPosition(), shipEntity.getPosition())<shipEntity.getCollisionRadius()+asteroids[i]->getCollisionRadius()
					&& shipEntity.isAlive()
					&& asteroids[i]->isAlive()) {
            // Whatever happens when the ship dies
            asteroids[i]->destroyed();
            shipEntity.destroyed();
            
            executeDestroyAction(*asteroids[i]);
            executeDestroyAction(shipEntity);
        }
    }

    // Check if the missiles hit anything
	for(unsigned int i = 0; i < missiles.size(); i++) {
		for(unsigned int j = 0; j < asteroids.size(); j++) {
			if(GeoMaths::distanceBetweenPoints(missiles[i]->getPosition(), asteroids[j]->getPosition())<asteroids[j]->getCollisionRadius()+missiles[i]->getCollisionRadius()
					&& asteroids[j]->isAlive()
					&& missiles[i]->isAlive()) {
				// Missile and asteroid are dead
                missiles[i]->destroyed();
                asteroids[j]->destroyed();
                executeDestroyAction(*asteroids[j]);
			}
		}
	}
}

void MainWindow::executeDestroyAction(Entity& destroyedEntity) {
	switch(destroyedEntity.getType()){
	case Entity::Asteroid: // Asteroid hit
		//increase score
		//splitLargeAsteroid(position);
		break;
	case Entity::Missile: //Medium asteroid hit
		//increase score by 1
		//split
		//splitMediumAsteroid(position);
		break;
	case Entity::Ship: //Ship hit
		//Game over
		break;
	case Entity::Unknown:
		break;
	}
}

void MainWindow::resetGame() {
	destroyEntities();
	score = 0;
	createShip();
	createAsteroids();
}

void MainWindow::prepareScore() {
	aFont.loadFromFile("Resources/arial.ttf");

	scoreText.setCharacterSize(30);
	scoreText.setStyle(sf::Text::Regular);
	scoreText.setFillColor(sf::Color::White);
}

void MainWindow::updateScore() {
	std::string scoreString = static_cast<std::ostringstream*>(&(std::ostringstream() << score))->str();
	scoreText.setString("Score: " + scoreString);
}

void MainWindow::destroyEntities() {

}
