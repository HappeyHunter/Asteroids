/*
 * ScoreKeeper.cpp
 *
 *  Created on: 2 May 2015
 *      Author: David
 */

#include "ScoreKeeper.h"
#include "Constants.h"

#include <sstream>

ScoreKeeper::ScoreKeeper() : score {0}, livesCount{3}, aFont{}, scoreText {"Score: ", aFont} {
	aFont.loadFromFile("Resources/arial.ttf");

	scoreText.setCharacterSize(30);
	scoreText.setStyle(sf::Text::Regular);
	scoreText.setFillColor(sf::Color::White);
    
    setupLives();
}

void ScoreKeeper::setupLives()
{
    lifeTexture.loadFromFile("Resources/Ship.png");
    
    for(int i = 0; lives.size() < MAX_LIVES; ++i) {
        lives.emplace_back(sf::Sprite(lifeTexture));
    }
    
    sf::Vector2f lifePos {0, scoreText.getLocalBounds().height + 20};
    
    for(unsigned int i = 0; i < lives.size(); ++i) {
        lifePos.x = lifeTexture.getSize().x * i;
        
        lives.at(i).setPosition(lifePos);
    }
}

void ScoreKeeper::respawn()
{
    --livesCount;
}

ScoreKeeper::~ScoreKeeper() {
	
}

void ScoreKeeper::increaseScore(int increase)
{
    score += increase;
    
    if(livesCount < MAX_LIVES && score / BONUS_POINTS_SCORE > (score-increase) / BONUS_POINTS_SCORE) {
        ++livesCount;
    }
}

int ScoreKeeper::getScore()
{
    return score;
}

void ScoreKeeper::reset()
{
    score = 0;
    livesCount = 3;
}

void ScoreKeeper::updateScore() {
	std::string scoreString = static_cast<std::ostringstream*>(&(std::ostringstream() << score))->str();
	scoreText.setString("Score: " + scoreString);
}

void ScoreKeeper::drawScore(sf::RenderWindow& window)
{
    window.draw(scoreText);
    
    for(int i = 0; i < livesCount; ++i) {
        window.draw(lives.at(i));
    }
}

int ScoreKeeper::getLivesCount()
{
    return livesCount;
}

