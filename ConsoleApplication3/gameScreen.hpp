#include "cScreen.h"
#include "enemy.hpp"
#include "player.hpp"
#include "enemyBullet.hpp"
#include "playerBullet.hpp"
#include "points.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Rect.hpp"
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameScreen : public CScreen
{
private:
    Enemy enemy[40];
    sf::Texture bg;
    sf::Sprite background;
    Player player;
    PlayerBullet playerBullet;
    EnemyBullet enemyBullet[40];
    int enemyShotChance[40];
	sf::SoundBuffer normalBuffer;
	sf::SoundBuffer hardBuffer;
	sf::Sound sound;
public:
    GameScreen(void);
    virtual int Run(sf::RenderWindow &App);
};

GameScreen::GameScreen(void)
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

	bg.loadFromFile("Images/spaceBackground.jpg");
	background.setTexture(bg, true);

	normalBuffer.loadFromFile("Audio/CytusR-VitMaster-Sakuzyo.ogg");
	hardBuffer.loadFromFile("Audio/Cytus09-DevilinWonderland-VILA[ChapterRRetro_.ogg");
	sound.setBuffer(normalBuffer);
	
}

int GameScreen::Run(sf::RenderWindow &App)
{
    sf::Event Event;

	sf::Font font;
	sf::Text score;
	sf::Text level;
	sf::Text goodLuck;
	sf::Text timer;
	sf::Text life;
	sound.play();
	sound.setLoop(true);

	int playerPoints = points;
	int levelNumber = 1;

	if (!font.loadFromFile("Xeron.ttf"))
		return -1;

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
	float enemyBulletSpeed = 0.20;
	int enemyFireChance = 10;
	bool checkRemainingEnemies;
	bool songChance = false;
	int timeLeft = 100000;

    bool isRunning = true;

    while (isRunning)
    {
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                return -1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && playerPosX > 120)
            {
                player.getSprite().move(-15,0);
                playerPosX -= 15;
            }
               
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && playerPosX < 660)
            {
                player.getSprite().move(15,0);
                playerPosX += 15;
            }
                
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !playerBullet.getBulletPresent())
               {
					playerBullet.getSprite().setPosition(playerPosX, playerPosY);
					playerBulletPosX = playerPosX;
					playerBulletPosY = playerPosY;
					playerBullet.setBulletPresent(true);
               }
        }

		if (!songChance && levelNumber > 3)
		{
			songChance = true;
			sound.setBuffer(hardBuffer);
			sound.play();
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

		goodLuck.setFont(font);
		goodLuck.setColor(sf::Color::Red);
		goodLuck.setCharacterSize(80);
		goodLuck.setString("GOOD LUCK");
		goodLuck.setPosition(100, 300);

		timer.setFont(font);
		timer.setColor(sf::Color::White);
		timer.setCharacterSize(10);
		timer.setString("Time: " + to_string(timeLeft));
		timer.setPosition(700, 575);

		life.setFont(font);
		life.setColor(sf::Color::White);
		life.setCharacterSize(16);
		life.setString("Lives: " + to_string(player.getLives()));
		life.setPosition(700, 500);

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
                    enemyBullet[i].setEnemyBulletPresent(true);
                }
            }

            for (int i = 0; i < 40; i++)
            {
                if (enemyBullet[i].getEnemyBulletPresent() && !resetEnemyBullet)
                {
                    enemyBullet[i].getSprite().setPosition(enemy[i].getSprite().getPosition());
                }
            }

            resetEnemyBullet = true;
        }
       
        for (int i = 0; i < 40; i++)
        {
			if (enemyBullet[i].getEnemyBulletPresent())
				enemyBullet[i].getSprite().move(0, enemyBulletSpeed);
        }

        if (enemyBulletDuration < 0)
        {
            resetEnemyBullet = false;
            enemyBulletDuration = enemyBulletDurationLevel;
            enemyBulletFired = false;
            for (int i = 0; i < 40; i++)
            {
                enemyBullet[i].setEnemyBulletPresent(false);
            }
        }

        enemyBulletDuration--;
        
		for (int i = 0; i < 40; i++)
		{
			if (playerBullet.getSprite().getGlobalBounds().intersects(enemy[i].getSprite().getGlobalBounds()) && enemy[i].getIsAlive() && playerBullet.getBulletPresent() && !enemy[i].getEnemyInvincible())
			{
				enemy[i].setIsAlive(false);
				playerPoints += enemy[i].getPoints();
				playerBullet.setBulletPresent(false);
			}
		}

		for (int i = 0; i < 40; i++)
		{
			if (player.getSprite().getGlobalBounds().intersects(enemyBullet[i].getSprite().getGlobalBounds()) && enemyBullet[i].getEnemyBulletPresent())
			{
				enemyBullet[i].setEnemyBulletPresent(false);
				player.removeLife();
				if (player.getLives() == 0)
					isRunning = false;
			}
		}

		if (time == 0)
		{
			player.removeLife();
			if (player.getLives() == 0)
				isRunning = false;

			timeLeft = 100000;
		}

		

        if (enemyMoveValue < 0)
            enemyMoveRight = true;

		if (enemyMoveValue > 4)
			enemyMoveRight = false;
		

        if (enemyMoveRight)
        {
            for (int i = 0; i < 10; i++)
            {
                enemy[i].getSprite().move(0.02, 0);
            }

			for (int i = 10; i < 20; i++)
			{
				enemy[i].getSprite().move(-0.02, 0);
			}

			for (int i = 20; i < 30; i++)
			{
				enemy[i].getSprite().move(0.02, 0);
			}

			for (int i = 30; i < 40; i++)
			{
				enemy[i].getSprite().move(-0.02, 0);
			}

            enemyMoveValue += 0.0010;
        }

        if (!enemyMoveRight)
        {
            for (int i = 0; i < 10; i++)
            {
                enemy[i].getSprite().move(-0.02, 0);
            }

			for (int i = 10; i < 20; i++)
			{
				enemy[i].getSprite().move(0.02, 0);
			}

			for (int i = 20; i < 30; i++)
			{
				enemy[i].getSprite().move(-0.02, 0);
			}

			for (int i = 30; i < 40; i++)
			{
				enemy[i].getSprite().move(0.02, 0);
			}

            enemyMoveValue -= 0.0010;
        }

        if (playerBullet.getBulletPresent())
        {
            playerBullet.getSprite().move(0, -1);
            playerBulletPosY -= 1;
        }

        if (playerBulletPosY < 0)
            playerBullet.setBulletPresent(false);

		timeLeft--;

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
            if (enemyBullet[i].getEnemyBulletPresent())
                App.draw(enemyBullet[i].getSprite());
        }

        App.draw(player.getSprite());
		App.draw(score);
		App.draw(level);

		if (levelNumber > 3)
			App.draw(goodLuck);

		if (enemy[0].getEnemyInvincible() && enemy[0].getEnemyInvincibilityTime() > 0)
		{
			enemy[0].decreaseInvincibilityTime();
		}

		if (enemy[0].getEnemyInvincibilityTime() == 0)
		{
			for (int i = 0; i < 40; i++)
			{
				enemy[i].setEnemyInvincible(false);
				enemy[i].setEnemyInvincibilityTime(500);
			}
		}

		checkRemainingEnemies = false;

		for (int i = 0; i < 40; i++)
		{
			if (enemy[i].getIsAlive())
				checkRemainingEnemies = true;
		}

		if (!checkRemainingEnemies)
		{
			playerBullet.setBulletPresent(false);

			for (int i = 0; i < 40; i++)
				enemy[i].setEnemyInvincible(true);

			levelNumber++;
			if (enemyFireChance > 1)
				enemyFireChance -= 3;
			if (enemyBulletDuration > 1000)
				enemyBulletDurationLevel -= 1000;
			if (enemyBulletDuration == 1000 && levelNumber == 6)
				enemyBulletDuration -= 500;
			if (enemyBulletDuration == 500 && levelNumber == 8)
				enemyBulletDuration -= 250;
			if (enemyBulletSpeed < 3)
				enemyBulletSpeed += 0.20;

			for (int i = 0; i < 40; i++)
			{
				enemy[i].setIsAlive(true);
			}
			timeLeft = 100000;
		}
		points = playerPoints;

		App.draw(life);
		App.draw(timer);
        App.display();
    }

    return 2;
}


