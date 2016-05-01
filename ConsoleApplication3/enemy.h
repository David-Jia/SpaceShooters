#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include "SFML/Graphics.hpp"
//#include "Bullet.h"

using namespace std;

class Enemy{
	private:
		sf::Sprite enemySprite;
		sf::Texture enemyTexture;
		int points,
			health;

		sf::Clock bulletReload;
		float bulletReloadRate;

	public:
		Enemy();
		Enemy(sf::Texture& texture, int points, int health);

		sf::Sprite& getSprite();
		int getPoints();
		int getHealth();
		bool isDead();

		void shoot();
		void hit();
};

#endif //ENEMY_H_INCLUDED