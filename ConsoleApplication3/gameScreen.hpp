#include "cScreen.h"
#include "enemy.hpp"
#include "player.hpp"
#include "enemyBullet.hpp"
#include "playerBullet.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class gameScreen : public CScreen
{
private:
    Enemy enemy[50];
    sf::Texture bg;
    sf::Sprite background;
    Player player;
    PlayerBullet playerBullet;
    EnemyBullet enemyBullet[50];
    int enemyShotChance[50];
    bool enemyBulletPresent[50];
public:
    gameScreen(void);
    virtual int Run(sf::RenderWindow &App);
};

gameScreen::gameScreen(void)
{
    float enemyPosX = 150;
    float enemyPosY = 100;
    float playerPosx = 400;
    float playerPosY = 550;
    float playerBulletPosx = playerPosx;
    float playerBulletPosy = playerPosY;
    for (int i = 0; i < 50; i++)
    {
        enemy[i].getSprite().setPosition(enemyPosX, enemyPosY);
        enemyPosX += 50;
        if (enemyPosX == 650)
        {
            enemyPosX = 150;
            enemyPosY += 50;
        }
    }
   
    player.getSprite().setPosition(400, 550);
   
    for (int i = 0; i < 50; i++)
    {
        enemyBulletPresent[i] = false;
    }

    bg.loadFromFile("Images/spaceBackground.jpg");
    background.setTexture(bg, true);
}

int gameScreen::Run(sf::RenderWindow &App)
{
    sf::Event Event;
    float playerPosX = 400;
    float playerPosY = 550;
    float playerBulletPosX = playerPosX;
    float playerBulletPosY = playerPosY;
    int bulletFiredBy = 0;
    bool enemyBulletFired = false;
    bool resetEnemyBullet = false;
    float enemyMoveValue = 2;
    bool enemyMoveRight = false;
    int enemyBulletDuration = 5000;
   
    bool isRunning = true;

    while (isRunning)
    {
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                return -1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerPosX > 0)
            {
                player.getSprite().move(-10,0);
                playerPosX -= 10;
            }
               
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerPosX < 770)
            {
                player.getSprite().move(10,0);
                playerPosX += 10;
            }
                
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !playerBullet.getBulletPresent())
               {
                   playerBullet.getSprite().setPosition(playerPosX, playerPosY);
                playerBulletPosX = playerPosX;
                playerBulletPosY = playerPosY;
                playerBullet.setBulletPresent(true);
               }
        }

        srand(time(0));

        for (int i = 0; i < 50; i++)
        {
            enemyShotChance[i] = rand() % 10;
        }

        if (!enemyBulletFired)
        {
            bulletFiredBy = (rand() % 10);
            enemyBulletFired = true;
        }

        if (enemyBulletFired)
        {
            for (int i = 0; i < 50; i++)
            {
                if ((enemyShotChance[i] == bulletFiredBy) && !resetEnemyBullet)
                {
                    enemyBulletPresent[i] = true;
                }
            }

            for (int i = 0; i < 50; i++)
            {
                if (enemyBulletPresent[i] && !resetEnemyBullet)
                {
                    enemyBullet[i].getSprite().setPosition(enemy[i].getSprite().getPosition());
                }
            }

            resetEnemyBullet = true;
        }
       
        for (int i = 0; i < 50; i++)
        {
            if (enemyBulletPresent[i])
                enemyBullet[i].getSprite().move(0, 0.10);
        }

        if (enemyBulletDuration < 0)
        {
            resetEnemyBullet = false;
            enemyBulletDuration = 5000;
            enemyBulletFired = false;
            for (int i = 0; i < 50; i++)
            {
                enemyBulletPresent[i] = false;
            }
        }

        enemyBulletDuration--;
       
       

        if (enemyMoveValue < 0)
            enemyMoveRight = true;

        if (enemyMoveValue > 4)
            enemyMoveRight = false;

        if (enemyMoveRight)
        {
            for (int i = 0; i < 50; i++)
            {
                enemy[i].getSprite().move(0.005, 0);
            }

            enemyMoveValue += 0.0005;
        }

        if (!enemyMoveRight)
        {
            for (int i = 0; i < 50; i++)
            {
                enemy[i].getSprite().move(-0.005, 0);
            }

            enemyMoveValue -= 0.0005;
        }

        if (playerBullet.getBulletPresent())
        {
            playerBullet.getSprite().move(0, -0.5);
            playerBulletPosY -= 0.5;
        }

        if (playerBulletPosY < 0)
            playerBullet.setBulletPresent(false);

        App.clear();

        App.draw(background);

        for (int i = 0; i < 50; i++)
        {
            App.draw(enemy[i].getSprite());
        }

        if (playerBullet.getBulletPresent())
            App.draw(playerBullet.getSprite());
       
        for (int i = 0; i < 50; i++)
        {
            if (enemyBulletPresent[i])
                App.draw(enemyBullet[i].getSprite());
        }

        App.draw(player.getSprite());
        App.display();
    }

    return 0;
}


