#include "cScreen.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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


}

int Screen_1::Run(sf::RenderWindow &App)
{
	sf::Event Event; 
	float playerPosx = 400;
	float playerPosY = 550;
    float playerBulletPosx = playerPosx;
	float playerBulletPosy = playerPosY;
	bool bulletPresent = false;
	float enemyMoveValue = 2;
	bool enemyMoveRight = false;
	
	bool isRunning = true;

	while (isRunning)
	{
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				return -1;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerPosx > 0)
			{
				player.move(-10,0);
				playerPosx -= 10;
			}
                
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerPosx < 770)
            {
            	player.move(10,0);
            	playerPosx += 10;
            }
                 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !bulletPresent)
           	{
           	    playerBullet.setPosition(playerPosx, playerPosY);
				playerBulletPosx = playerPosx;
				playerBulletPosy = playerPosY;
				bulletPresent = true;
           	}
		}

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
			playerBulletPosy -= 0.5;
		}

		if (playerBulletPosy < 0)
			bulletPresent = false;

		App.clear();

		App.draw(background);

		for (int i = 0; i < 50; i++)
		{
			App.draw(enemy[i]);
		}

		if (bulletPresent)
			App.draw(playerBullet);

		App.draw(player);
		App.display();
	}

	return 0;
}
