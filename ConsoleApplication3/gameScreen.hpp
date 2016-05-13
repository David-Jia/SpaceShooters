#include "cScreen.h"
#include "enemy.hpp"
#include "player.hpp"
#include "enemyBullet.hpp"
#include "playerBullet.hpp"
#include <SFML/Graphics.hpp>
#include "Rect.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class gameScreen : public CScreen
{
private:
    Enemy enemy[40];
    sf::Texture bg;
    sf::Sprite background;
    Player player;
    PlayerBullet playerBullet;
    EnemyBullet enemyBullet[40];
    int enemyShotChance[40];
    bool enemyBulletPresent[40];
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
	for (int i = 0; i < 40; i++)
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

	for (int i = 0; i < 40; i++)
	{
		enemyBulletPresent[i] = false;
	}

	bg.loadFromFile("Images/spaceBackground.jpg");
	background.setTexture(bg, true);

	
}

int gameScreen::Run(sf::RenderWindow &App)
{
    sf::Event Event;

	sf::Font font;
	sf::Text score;
	sf::Text level;
	int points = 0;
	int levelNumber = 1;

	if (!font.loadFromFile("Xeron.ttf"))
		return -1;

	score.setFont(font);
	score.setColor(sf::Color::White);
	score.setCharacterSize(12);
	score.setString("Score: " + to_string(points));
	score.setPosition(680, 550);

	level.setFont(font);
	level.setColor(sf::Color::White);
	level.setCharacterSize(12);
	level.setString("Level: " + to_string(levelNumber));
	level.setPosition(680, 525);

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
	int enemyBulletDurationLevel = 5000;
	float enemyBulletSpeed = 0.10;
	int enemyFireChance = 10;
	bool checkRemainingEnemies;

    bool isRunning = true;

    while (isRunning)
    {
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                return -1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerPosX > 100)
            {
                player.getSprite().move(-10,0);
                playerPosX -= 10;
            }
               
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerPosX < 670)
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

        for (int i = 0; i < 40; i++)
        {
            enemyShotChance[i] = rand() % enemyFireChance;
        }

        if (!enemyBulletFired)
        {
            bulletFiredBy = (rand() % enemyFireChance);
            enemyBulletFired = true;
        }

        if (enemyBulletFired)
        {
            for (int i = 0; i < 40; i++)
            {
                if ((enemyShotChance[i] == bulletFiredBy) && !resetEnemyBullet && enemy[i].getIsAlive())
                {
                    enemyBulletPresent[i] = true;
                }
            }

            for (int i = 0; i < 40; i++)
            {
                if (enemyBulletPresent[i] && !resetEnemyBullet)
                {
                    enemyBullet[i].getSprite().setPosition(enemy[i].getSprite().getPosition());
                }
            }

            resetEnemyBullet = true;
        }
       
        for (int i = 0; i < 40; i++)
        {
			if (enemyBulletPresent[i])
				enemyBullet[i].getSprite().move(0, enemyBulletSpeed);
        }

        if (enemyBulletDuration < 0)
        {
            resetEnemyBullet = false;
            enemyBulletDuration = enemyBulletDurationLevel;
            enemyBulletFired = false;
            for (int i = 0; i < 40; i++)
            {
                enemyBulletPresent[i] = false;
            }
        }

        enemyBulletDuration--;
        
		for (int i = 0; i < 40; i++)
		{
			if (playerBullet.getSprite().getGlobalBounds().intersects(enemy[i].getSprite().getGlobalBounds()) && enemy[i].getIsAlive())
			{
				enemy[i].setIsAlive(false);
				points += enemy[i].getPoints();
				playerBullet.setBulletPresent(false);
			}
		}

		for (int i = 0; i < 40; i++)
		{
			if (player.getSprite().getGlobalBounds().intersects(enemyBullet[i].getSprite().getGlobalBounds()))
			{
				isRunning = false;
			}
		}

		score.setFont(font);
		score.setColor(sf::Color::White);
		score.setCharacterSize(10);
		score.setString("Score: " + to_string(points));
		score.setPosition(700, 550);

		level.setFont(font);
		level.setColor(sf::Color::White);
		level.setCharacterSize(10);
		level.setString("Level: " + to_string(levelNumber));
		level.setPosition(700, 525);

        if (enemyMoveValue < 0)
            enemyMoveRight = true;

		if (enemyMoveValue > 4)
			enemyMoveRight = false;
		

        if (enemyMoveRight)
        {
            for (int i = 0; i < 40; i++)
            {
                enemy[i].getSprite().move(0.02, 0);
            }

            enemyMoveValue += 0.0010;
        }

        if (!enemyMoveRight)
        {
            for (int i = 0; i < 40; i++)
            {
                enemy[i].getSprite().move(-0.02, 0);
            }

            enemyMoveValue -= 0.0010;
        }

        if (playerBullet.getBulletPresent())
        {
            playerBullet.getSprite().move(0, -.75);
            playerBulletPosY -= .75;
        }

        if (playerBulletPosY < 0)
            playerBullet.setBulletPresent(false);

        App.clear();

        App.draw(background);

        for (int i = 0; i < 40; i++)
        {
			if (enemy[i].getIsAlive())
				App.draw(enemy[i].getSprite());
        }

        if (playerBullet.getBulletPresent())
            App.draw(playerBullet.getSprite());
       
        for (int i = 0; i < 40; i++)
        {
            if (enemyBulletPresent[i])
                App.draw(enemyBullet[i].getSprite());
        }

        App.draw(player.getSprite());
		App.draw(score);
		App.draw(level);

		checkRemainingEnemies = false;

		for (int i = 0; i < 40; i++)
		{
			if (enemy[i].getIsAlive())
				checkRemainingEnemies = true;
		}

		if (!checkRemainingEnemies)
		{
			levelNumber++;
			if (enemyFireChance > 2)
				enemyFireChance -= 2;
			if (enemyFireChance == 2 && levelNumber > 5)
				enemyFireChance -= 1;
			if (enemyBulletDuration > 1000)
				enemyBulletDurationLevel -= 1000;
			if (enemyBulletDuration == 1000 && levelNumber == 6)
				enemyBulletDuration -= 500;
			if (enemyBulletDuration == 500 && levelNumber == 8)
				enemyBulletDuration -= 250;
			if (enemyBulletSpeed < 3)
				enemyBulletSpeed += 0.10;

			for (int i = 0; i < 40; i++)
			{
				enemy[i].setIsAlive(true);
			}
		}

        App.display();
    }

    return 0;
}


