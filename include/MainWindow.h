/*
 * MainWindow.h
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "Entity.h"
#include "ScoreKeeper.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class MainWindow {
public:
	MainWindow();
	virtual ~MainWindow();
	int runGame();

public:
	static const int gameWidth = 800;
	static const int gameHeight = 800;

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
	void splitAsteroid(const sf::Vector2f&, Entity&);
	void resetGame();
	void destroyEntities();
    void drawEntity(sf::RenderWindow&, Entity&);
    bool isSpawnEmpty();
    void prepareLives();

private:
	std::vector<bool> shipCommands;
    ScoreKeeper score;
    sf::Rect<float> spawnArea;
    int spawnDelay;
    sf::Vector2f centre;
};

#endif /* MAINWINDOW_H_ */
