#include "SFML/Graphics.hpp"

using namespace std;

class Enemy{
	private:
		sf::Sprite enemySprite;
		sf::Texture enemyTexture;
		int points,
			health;

	public:
		Enemy();
		sf::Sprite& getSprite();
		int getPoints();	
};

Enemy::Enemy()
{
	enemyTexture.loadFromFile("Images/Enemy.png");
	enemySprite.setTexture(enemyTexture, true);
	points = 100;
}

sf::Sprite& Enemy::getSprite()
{
	return enemySprite;
}

int Enemy::getPoints()
{
	return points;
}