/*
 * MainWindow.cpp
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#define TICK 1

#include "Constants.h"
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

std::vector<std::unique_ptr<Asteroid>> asteroids;
std::vector<std::unique_ptr<Missile>> missiles;

bool reloading = false;

const int asteroidCount = 8;

MainWindow::MainWindow() : centre { (float) gameWidth/2, (float) gameHeight/2} {    
    sf::Vector2f centreSize {(float) gameWidth/5, (float) gameHeight/5};
    sf::Vector2f centreRectPos {(float) gameWidth/2-centreSize.x/2, (float) gameHeight/2-centreSize.y/2};
    
    spawnArea = sf::Rect<float>(centreRectPos, centreSize);
    
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
        score.updateScore();
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
    if(shipEntity.isAlive()) {
        shipEntity.tick(TICK);
    } else {
        // Ship is dead. Wait out the delay, then try to respawn the ship when nothing is in the centre
        if(spawnDelay <= 0) {
            if(score.getLivesCount() < 0) {
                // gameOver();
            } else if(isSpawnEmpty()) {
                sf::Vector2f spawnPos;

                spawnPos.x = gameWidth/2;
                spawnPos.y = gameHeight/2;

                shipEntity.respawnShip(spawnPos);
                score.respawn();
            }
        } else {
            --spawnDelay;
        }
    }

    // Asteroids
    if(asteroids.size() > 0) {
        for(unsigned int i = 0; i < asteroids.size(); i++) {
            asteroids[i]->tick(TICK);
        }
    } else {
        createAsteroids();
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
        do {
		startPos.x = rand() % gameWidth;
		startPos.y = rand() % gameHeight;
        } while(spawnArea.contains(startPos));

		asteroids.emplace_back(new Asteroid(Asteroid::Large, startPos));
	}

	return 0;
}

void MainWindow::processKeyPress(sf::Event event) {
    
    if(shipEntity.isAlive()) {
        if(event.key.code == sf::Keyboard::Space && !reloading) {
            missiles.emplace_back(new Missile(shipEntity.getPosition(), shipEntity.getAngle()+180));
            reloading = true;
        } else if(event.key.code == sf::Keyboard::BackSpace) {
            resetGame();
        } else if(event.key.code != sf::Keyboard::Unknown) {
            shipCommands[event.key.code] = true;
        }
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
		drawEntity(window, *asteroids[i]);
	}

	for(unsigned int i = 0; i < missiles.size(); i++) {
		drawEntity(window, *missiles[i]);
	}

	drawEntity(window, shipEntity);

	score.drawScore(window);

	window.display();
}

void MainWindow::drawEntity(sf::RenderWindow& window, Entity& entity)
{
    if(entity.isAlive()) {
        window.draw(entity.getSprite());
    }
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
            // Ship is destroyed
            shipEntity.destroyed();
            
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
        score.increaseScore(destroyedEntity.getScoreValue());
		splitAsteroid(destroyedEntity.getPosition(), destroyedEntity);
		break;
	case Entity::Ship: //Ship hit
		//Life lost, respawn in a bit
        spawnDelay = 60;
		break;
    case Entity::Missile:
	case Entity::Unknown:
		break;
	}
}

void MainWindow::splitAsteroid(const sf::Vector2f& position, Entity& destroyedEntity) {
    sf::Vector2f startPos;
    Asteroid& destroyedAsteroid = dynamic_cast<Asteroid&>(destroyedEntity);
    
    Asteroid::Size newSize {Asteroid::Small};
    
    if(destroyedAsteroid.getSize() == Asteroid::Small) {
        return;
    } else if(destroyedAsteroid.getSize() == Asteroid::Large) {
        newSize = Asteroid::Medium;
    }
    
	asteroids.emplace_back(new Asteroid(newSize, position));
    asteroids.emplace_back(new Asteroid(newSize, position));
}

void MainWindow::resetGame() {
	destroyEntities();
	score.reset();
	createShip();
	createAsteroids();
}

void MainWindow::destroyEntities() {

}

bool MainWindow::isSpawnEmpty()
{
    bool empty {true};
    
    // Asteroids
    for(unsigned int i = 0; i < asteroids.size() && empty; i++) {
		if(GeoMaths::distanceBetweenPoints(asteroids[i]->getSprite().getPosition(), centre) < asteroids[i]->getCollisionRadius() + shipEntity.getCollisionRadius()*4) {
            empty = false;
        }
	}	
	
	return empty;
}
