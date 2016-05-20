// Second screen, the actual game is played here
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
	sf::SoundBuffer hitBuffer;
	sf::Sound sound;
	sf::Sound hit;
	float playerPosX;
	float playerPosY;
	float playerBulletPosX;
	float playerBulletPosY;
public:
    GameScreen(void);
    virtual int Run(sf::RenderWindow &App);
	// Summary: This function runs the event that appear in the screen
	// Precondition: Takes in a number that determines which virtual Run class will run
	// Postcondition: The screen number that corresponds with the input will run
	void enemyMove(float& enemyMoveVal, bool& enemyMoveRight);
	// Summary: This function makes sure that the enemies move to the left and to the right
	// Precondition: Takes in the enemies move value and if they are moving right
	// Postcondition: Moves the enemy sprites depending on the arguments
};

GameScreen::GameScreen(void)
{
	// Positions based on pixels
	float enemyPosX = 150;
	float enemyPosY = 100;
	playerPosX = 400;
	playerPosY = 550;
	playerBulletPosX = playerPosY;
	playerBulletPosY = playerPosY;
	for (int i = 0; i < 40; i++) // Sets the positions for all 40 enemies
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

	// Loads in the audio files
	normalBuffer.loadFromFile("Audio/09ComeandFindMe-Bmix.ogg");
	hardBuffer.loadFromFile("Audio/01ANightOfDizzySpells.ogg");
	hitBuffer.loadFromFile("Audio/Explosion.ogg");
	sound.setBuffer(normalBuffer);
	hit.setBuffer(hitBuffer);
	hit.setVolume(50);
	
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
	// Plays the normal nackground music and makes sure it loops
	sound.play();
	sound.setLoop(true);

	int playerPoints = points;
	int levelNumber = 1;

	if (!font.loadFromFile("Xeron.ttf"))
		return -1;

    int bulletFiredBy = 0; // if the enemy shot chance is equal to this, the corresponding enemy fires a shot
    bool enemyBulletFired = false;
    bool resetEnemyBullet = false; // used to see whether or not the enemies can shoot again
    float enemyMoveValue = 2; // used to determine when the enemy movement would change direction
    bool isEnemyMoveRight = false; // used to see which direction the enemies are moving
    int enemyBulletDuration = 5000; // used to determine when the enemy bullets would reset in level 1
	int enemyBulletDurationLevel = 5000; // same as the enemyBulletDuration except this is used for level 2 onwards
	float enemyBulletSpeed = 0.20; // the number of pixels that the enemy bullets move per game loop
	int enemyFireChance = 10; // the initial chance for the enemy to shoot
	bool checkRemainingEnemies; 
	bool songChance = false; // used to trigger the song change
	int timeLeft = 100000; // how much time the player has per level

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

		if (!songChance && levelNumber > 3) // changes the music once the hard levels (4+) begin
		{
			songChance = true;
			sound.setBuffer(hardBuffer);
			sound.play();
		}

		//********Current Game Information in the bottom right corner*********
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
		//**********************************************************************

		goodLuck.setFont(font);
		goodLuck.setColor(sf::Color::Red);
		goodLuck.setCharacterSize(80);
		goodLuck.setString("GOOD LUCK");
		goodLuck.setPosition(100, 300);

        srand(time(0)); // random

		//*******************EnemyBullet related code***************************
        for (int i = 0; i < 40; i++) // sets the shooting chance of each enemy
        {
            enemyShotChance[i] = rand() % enemyFireChance;
        }

        if (!enemyBulletFired) // if the enemybullets are currently not active, sets it to true and also determines which enemies would actually fire
        {
            bulletFiredBy = (rand() % enemyFireChance);
            enemyBulletFired = true;
        }

        if (enemyBulletFired) // if the enemy at the corresponding spot is alive and they are suppose to fire, then it sets the enemyBullets for those enemies to true
        {					  // afterwards the enemyBullet sprites would be placed at the enemies that are firing
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
       
        for (int i = 0; i < 40; i++) // if the bullet that enemy is present, it would move
        {
			if (enemyBullet[i].getEnemyBulletPresent())
				enemyBullet[i].getSprite().move(0, enemyBulletSpeed);
        }

        if (enemyBulletDuration < 0) // resets the enemy firing attributes for the next wave of bullets
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
       //***********************************************************************

		for (int i = 0; i < 40; i++) // checks for if the player bullet hits an enemy and if true, then removes the enemy and the attributes that are involved are changed
		{
			if (playerBullet.getSprite().getGlobalBounds().intersects(enemy[i].getSprite().getGlobalBounds()) && enemy[i].getIsAlive() && playerBullet.getBulletPresent() && !enemy[i].getEnemyInvincible())
			{
				enemy[i].setIsAlive(false);
				hit.play();
				playerPoints += enemy[i].getPoints();
				playerBullet.setBulletPresent(false);
			}
		}

		for (int i = 0; i < 40; i++) // checks if the player is hit by an enemy bullet and the attributes that are involved are changed
		{
			if (player.getSprite().getGlobalBounds().intersects(enemyBullet[i].getSprite().getGlobalBounds()) && enemyBullet[i].getEnemyBulletPresent())
			{
				enemyBullet[i].setEnemyBulletPresent(false);
				player.removeLife();
				hit.play();
				if (player.getLives() == 0) // ends the game and goes to the game over screen if the player is out of lives
				{
					sound.stop();
					isRunning = false;
				}
			}
		}

		if (time == 0) // runs when the player is out of time for the level
		{
			player.removeLife();
			hit.play();
			if (player.getLives() == 0) // ends the game and goes to the game over screen if the player is out of lives
			{
				sound.stop();
				isRunning = false;
			}

			timeLeft = 100000;
		}

		enemyMove(enemyMoveValue, isEnemyMoveRight); // controls the enemy movement

        if (playerBullet.getBulletPresent()) // makes sure that the player bullet moves upward when fired
        {
            playerBullet.getSprite().move(0, -1);
            playerBulletPosY -= 1;
        }

        if (playerBulletPosY < 0) // removes the player bullet from existence when it exits the screen
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

		// lowers the enemy spawn invincibility time and removes their invincibility
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

		//*****Resets Enemies, moves onto the next level, and increases the difficulty when all enemies of the current level are killed****
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
		//****************************************************************************************************************
		points = playerPoints; // sets the point variables from the "points.h" file equal to the changes made from this file 

		App.draw(life);
		App.draw(timer);
        App.display();
    }

    return 2;
}

void GameScreen::enemyMove(float& enemyMoveVal, bool& enemyMoveRight)
{
	if (enemyMoveVal < 0) // enemies move to the right when they reach a certain distance to the left
		enemyMoveRight = true;

	if (enemyMoveVal > 4) // enemies move to the left when they reach a certain distance to the right
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

		enemyMoveVal += 0.0010;
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

		enemyMoveVal -= 0.0010;
	}
}


