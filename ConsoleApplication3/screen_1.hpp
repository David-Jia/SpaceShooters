#include "cScreen.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Screen_1 : public CScreen
{
private:
	sf::Sprite enemy[50];
	sf::Texture bg;
	sf::Sprite background;
	sf::Texture enemyPic;
	sf::Sprite player;
	sf::Texture playerPic;
	sf::Sprite playerBullet;
	sf::Sprite enemyBullet[50];
	sf::Texture playBullet;
	sf::Texture enemBullet;
	int enemyShotChance[50];
	bool enemyBulletPresent[50];
public: 
	Screen_1(void);
	virtual int Run(sf::RenderWindow &App);
};

Screen_1::Screen_1(void)
{
	float enemyPosX = 150;
	float enemyPosY = 100;
	float playerPosx = 400;
	float playerPosY = 550;
	float playerBulletPosx = playerPosx;
	float playerBulletPosy = playerPosY;
	enemyPic.loadFromFile("Images/Enemy.png");
	for (int i = 0; i < 50; i++)
	{
		enemy[i].setTexture(enemyPic, true);
		enemy[i].setPosition(enemyPosX, enemyPosY);
		enemyPosX += 50;
		if (enemyPosX == 650)
		{
			enemyPosX = 150;
			enemyPosY += 50;
		}
	}
	playBullet.loadFromFile("Images/PlayerBullet.png");
	playerBullet.setTexture(playBullet, true);
	//playerBullet.setPosition(400, 500);
	enemBullet.loadFromFile("Images/EnemyBullet.png");
	for (int i = 0; i < 50; i++)
	{
		enemyBullet[i].setTexture(enemBullet, true);
	}
	playerPic.loadFromFile("Images/Player.png");
	player.setTexture(playerPic, true);
	player.setPosition(400, 550);
	bg.loadFromFile("Images/spaceBackground.jpg");
	background.setTexture(bg, true);
	for (int i = 0; i < 50; i++)
	{
		if (i % 6 == 0)
			enemyShotChance[i] = 0;
		else if (i % 5 == 0)
			enemyShotChance[i] = 1;
		else if (i % 4 == 0)
			enemyShotChance[i] = 2;
		else if (i % 3 == 0)
			enemyShotChance[i] = 3;
		else if (i % 2 == 0)
			enemyShotChance[i] = 4;
	}

	for (int i = 0; i < 50; i++)
	{
		enemyBulletPresent[i] = false;
	}


}

int Screen_1::Run(sf::RenderWindow &App)
{
	sf::Event Event; 
	float playerPosX = 400;
	float playerPosY = 550;
    float playerBulletPosX = playerPosX;
	float playerBulletPosY = playerPosY;
	int bulletFiredBy = 0;
	bool bulletPresent = false;
	bool enemyBulletFired = false;
	bool resetEnemyBullet = false;
	float enemyMoveValue = 2;
	bool enemyMoveRight = false;
	int enemyBulletDuration = 2000;
	
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
				player.move(-10,0);
				playerPosX -= 10;
			}
                
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerPosX < 770)
            {
            	player.move(10,0);
            	playerPosX += 10;
            }
                 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !bulletPresent)
           	{
           	    playerBullet.setPosition(playerPosX, playerPosY);
				playerBulletPosX = playerPosX;
				playerBulletPosY = playerPosY;
				bulletPresent = true;
           	}
		}

		srand(time(0));

		if (!enemyBulletFired)
		{
			bulletFiredBy = (rand() % 5);
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
					enemyBullet[i].setPosition(enemy[i].getPosition());
				}
			}

			resetEnemyBullet = true;
		}
		
		for (int i = 0; i < 50; i++)
		{
			if (enemyBulletPresent[i])
				enemyBullet[i].move(0, 0.25);
		}

		if (enemyBulletDuration < 0)
		{
			resetEnemyBullet = false;
			enemyBulletDuration = 2000;
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
				enemy[i].move(0.005, 0);
			}

			enemyMoveValue += 0.0005;
		}

		if (!enemyMoveRight)
		{
			for (int i = 0; i < 50; i++)
			{
				enemy[i].move(-0.005, 0);
			}

			enemyMoveValue -= 0.0005;
		}

		if (bulletPresent)
		{
			playerBullet.move(0, -0.5);
			playerBulletPosY -= 0.5;
		}

		if (playerBulletPosY < 0)
			bulletPresent = false;

		App.clear();

		App.draw(background);

		for (int i = 0; i < 50; i++)
		{
			App.draw(enemy[i]);
		}

		if (bulletPresent)
			App.draw(playerBullet);
		
		for (int i = 0; i < 50; i++)
		{
			if (enemyBulletPresent[i])
				App.draw(enemyBullet[i]);
		}

		App.draw(player);
		App.display();
	}

	return 0;
}
