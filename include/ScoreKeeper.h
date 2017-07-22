/*
 * ScoreKeeper.h
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#ifndef SCOREKEEPER_H_
#define SCOREKEEPER_H_

#include <SFML/Graphics.hpp>
#include <vector>

class ScoreKeeper {
public:
	ScoreKeeper();
	virtual ~ScoreKeeper();
    
    void increaseScore(int);
    int getScore();
    void reset();
    void updateScore();
    void drawScore(sf::RenderWindow&);
    int getLivesCount();
    void respawn();
    
private:
    void setupLives();
    
private:
    int score;
    int livesCount;
    sf::Font aFont;
    sf::Text scoreText;
    std::vector<sf::Sprite> lives;
	std::string lifeTextureLocation;
	sf::Texture lifeTexture;
};

#endif /* SCOREKEEPER_H_ */
