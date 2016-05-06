#include "enemy.h"
#include <iostream>

Enemy::Enemy()
{
	enemyTexture.loadFromFile("Images/Enemy.png");
	enemySprite.setTexture(enemyTexture, true);
	points = 100;
	health = 3;
	bulletReloadRate = 0.5f;
}

sf::Sprite& Enemy::getSprite()
{ 
	return enemySprite; 
}

int Enemy::getPoints() 
{ 
	return points; 
}

int Enemy::getHealth() 
{ 
	return health; 
}

bool Enemy::isDead() 
{ 
	return health == 0; 
}

void Enemy::shoot()
{
	bulletReload.restart();
}

void Enemy::hit()
{
	health--;
}