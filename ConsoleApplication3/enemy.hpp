#include "SFML/Graphics.hpp"

using namespace std;

class Enemy{
	private:
		sf::Sprite enemySprite;
		sf::Texture enemyTexture;
		int points;
		bool isAlive;
		bool enemyInvincible = false;
		int enemyInvincibilityTime = 500;

	public:
		// Constructors
		Enemy();
		// Getters
		sf::Sprite& getSprite();
		int getPoints();	
		bool getIsAlive();
		bool getEnemyInvincible();
		int getEnemyInvincibilityTime();
		// Setters
		void setIsAlive(bool alive);
		void setEnemyInvincible(bool invincible);
		void setEnemyInvincibilityTime(int invinciblitytime);
		// Other Methods
		void decreaseInvincibilityTime();
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

bool Enemy::getEnemyInvincible()
{
	return enemyInvincible;
}

int Enemy::getEnemyInvincibilityTime()
{
	return enemyInvincibilityTime;
}

void Enemy::setIsAlive(bool alive)
{
	isAlive = alive;
}

void Enemy::setEnemyInvincible(bool invincible)
{
	enemyInvincible = invincible;
}

void Enemy::setEnemyInvincibilityTime(int invincibilityTime)
{
	enemyInvincibilityTime = invincibilityTime;
}

void Enemy::decreaseInvincibilityTime()
{
	enemyInvincibilityTime--;
}
