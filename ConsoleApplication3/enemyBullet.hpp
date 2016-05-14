#include "SFML/Graphics.hpp"

using namespace std;

class EnemyBullet
{
private:
    sf::Sprite enemyBulletSprite;
    sf::Texture enemyBulletTexture;
	bool enemyBulletPresent;

public:
    //Constructors
    EnemyBullet();
    //Getters
    sf::Sprite& getSprite();
	bool getEnemyBulletPresent();
	// Setters
	void setEnemyBulletPresent(bool present);
};

EnemyBullet::EnemyBullet()
{
    enemyBulletTexture.loadFromFile("Images/EnemyBullet.png");
    enemyBulletSprite.setTexture(enemyBulletTexture, true);
	enemyBulletPresent = false;
}

sf::Sprite& EnemyBullet::getSprite()
{
    return enemyBulletSprite;
}

bool EnemyBullet::getEnemyBulletPresent()
{
	return enemyBulletPresent;
}

void EnemyBullet::setEnemyBulletPresent(bool present)
{
	enemyBulletPresent = present;
}