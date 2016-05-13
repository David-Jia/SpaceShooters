#include "SFML/Graphics.hpp"

using namespace std;

class EnemyBullet
{
private:
    sf::Sprite enemyBulletSprite;
    sf::Texture enemyBulletTexture;

public:
    //Constructors
    EnemyBullet();
    //Getters
    sf::Sprite& getSprite();
};

EnemyBullet::EnemyBullet()
{
    enemyBulletTexture.loadFromFile("Images/EnemyBullet.png");
    enemyBulletSprite.setTexture(enemyBulletTexture, true);
}

sf::Sprite& EnemyBullet::getSprite()
{
    return enemyBulletSprite;
}
