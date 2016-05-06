//#include <SFML/Sprite.hpp>
#include <stdio.h>
#include"bullet.h"

Bullet::Bullet()
{
    //numBullets = 0;
    //numHits = 0;
    hitRatio = 0;
    isTouchingPlayer = false;
    isTouchingEnemy = false;
    speed = 10;
    bulletType = false;
}
bool Bullet::isTouchingEntity()
{
    //if bullet is tuching enemy, then call enemy death function
    //if bullte is touching player, then call player death function
    
    //if the bullet sprite == any other sprite, it will call their death functions
}
