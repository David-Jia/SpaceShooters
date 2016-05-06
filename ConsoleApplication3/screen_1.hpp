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

public: 
	Screen_1(void);
	virtual int Run(sf::RenderWindow &App);
};

Screen_1::Screen_1(void)
{
	float enemyPosX = 150;
	float enemyPosY = 100;
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

	bg.loadFromFile("Images/spaceBackground.jpg");
	background.setTexture(bg);


}

int Screen_1::Run(sf::RenderWindow &App)
{
	sf::Event Event; 

	bool isRunning = true;

	while (isRunning)
	{
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				return -1;
			}
		}

		App.clear();

		for (int i = 0; i < 50; i++)
		{
			App.draw(enemy[i]);
		}

		App.display();
	}

	return 0;
}
