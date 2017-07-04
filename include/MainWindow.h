/*
 * MainWindow.h
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MainWindow {
public:
	MainWindow();
	virtual ~MainWindow();
	int runGame();

public:
	static const int gameWidth = 600;
	static const int gameHeight = 600;

private:
    void gameTick();
	int createShip();
	int createAsteroids();
	void checkCollisions();
	void processKeyPress(sf::Event);
	void processKeyRelease(sf::Event);
	void drawEntities(sf::RenderWindow&);
	void updatePositions();
	void executeShipCommands();
	void executeDestroyAction(Entity&);
	int splitLargeAsteroid(sf::Vector2f);
	int splitMediumAsteroid(sf::Vector2f);
	void resetGame();
	void destroyEntities();
	void prepareScore();
	void updateScore();

private:
	std::vector<bool> shipCommands;
};

#endif /* MAINWINDOW_H_ */
