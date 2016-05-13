#include "SFML/Graphics.hpp"

using namespace std;

class Enemy{
	private:
		sf::Sprite enemySprite;
		sf::Texture enemyTexture;
		int points;
		bool isAlive;

	public:
		// Constructors
		Enemy();
		// Getters
		sf::Sprite& getSprite();
		int getPoints();	
		bool getIsAlive();
		// Setters
		void setIsAlive(bool alive);
};

Enemy::Enemy()
{
	enemyTexture.loadFromFile("Images/Enemy.png");
	enemySprite.setTexture(enemyTexture, true);
	points = 10;
	isAlive = true;
}

sf::Sprite& Enemy::getSprite()
{
	return enemySprite;
}

int Enemy::getPoints()
{
	return points;
}

bool Enemy::getIsAlive()
{
	return isAlive;
}

void Enemy::setIsAlive(bool alive)
{
	isAlive = alive;
}

