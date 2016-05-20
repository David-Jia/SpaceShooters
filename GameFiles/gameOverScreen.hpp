// End screen, the last screen that is displayed
#include "cScreen.h"
#include "points.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class GameOverScreen : public CScreen
{
	private: 
		bool isRunning;
		// Needed to create a pseudo gif
		sf::Texture playerDeathTexture1;
		sf::Texture playerDeathTexture2;
		sf::Texture playerDeathTexture3;
		sf::Texture playerDeathTexture4;
		sf::Texture playerDeathTexture5;
		sf::Texture playerDeathTexture6;
		sf::Texture playerDeathTexture7;
		sf::Texture playerDeathTexture8;
		sf::Texture playerDeathTexture9;
		sf::Texture playerDeathTexture10;
		sf::Texture playerDeathTexture11;
		sf::Texture playerDeathTexture12;
		sf::Sprite playerDeathSprite1;
		sf::Sprite playerDeathSprite2;
		sf::Sprite playerDeathSprite3;
		sf::Sprite playerDeathSprite4;
		sf::Sprite playerDeathSprite5;
		sf::Sprite playerDeathSprite6;
		sf::Sprite playerDeathSprite7;
		sf::Sprite playerDeathSprite8;
		sf::Sprite playerDeathSprite9;
		sf::Sprite playerDeathSprite10;
		sf::Sprite playerDeathSprite11;
		sf::Sprite playerDeathSprite12;

	public:
		GameOverScreen(void);
		virtual int Run(sf::RenderWindow &App);
		// Summary: This function runs the event that appear in the screen
		// Precondition: Takes in a number that determines which virtual Run class will run
		// Postcondition: The screen number that corresponds with the input will run
};

GameOverScreen::GameOverScreen(void)
{
	isRunning = false;

	playerDeathTexture1.loadFromFile("Images/l0_PlayerDeath_01.png");
	playerDeathTexture2.loadFromFile("Images/l0_PlayerDeath_02.png");
	playerDeathTexture3.loadFromFile("Images/l0_PlayerDeath_03.png");
	playerDeathTexture4.loadFromFile("Images/l0_PlayerDeath_04.png");
	playerDeathTexture5.loadFromFile("Images/l0_PlayerDeath_05.png");
	playerDeathTexture6.loadFromFile("Images/l0_PlayerDeath_06.png");
	playerDeathTexture7.loadFromFile("Images/l0_PlayerDeath_07.png");
	playerDeathTexture8.loadFromFile("Images/l0_PlayerDeath_08.png");
	playerDeathTexture9.loadFromFile("Images/l0_PlayerDeath_09.png");
	playerDeathTexture10.loadFromFile("Images/l0_PlayerDeath_10.png");
	playerDeathTexture11.loadFromFile("Images/l0_PlayerDeath_11.png");
	playerDeathTexture12.loadFromFile("Images/l0_PlayerDeath_12.png");

	playerDeathSprite1.setTexture(playerDeathTexture1, true);
	playerDeathSprite2.setTexture(playerDeathTexture2, true);
	playerDeathSprite3.setTexture(playerDeathTexture3, true);
	playerDeathSprite4.setTexture(playerDeathTexture4, true);
	playerDeathSprite5.setTexture(playerDeathTexture5, true);
	playerDeathSprite6.setTexture(playerDeathTexture6, true);
	playerDeathSprite7.setTexture(playerDeathTexture7, true);
	playerDeathSprite8.setTexture(playerDeathTexture8, true);
	playerDeathSprite9.setTexture(playerDeathTexture9, true);
	playerDeathSprite10.setTexture(playerDeathTexture10, true);
	playerDeathSprite11.setTexture(playerDeathTexture11, true);
	playerDeathSprite12.setTexture(playerDeathTexture12, true);

	playerDeathSprite1.setPosition(400, 400);
	playerDeathSprite2.setPosition(400, 400);
	playerDeathSprite3.setPosition(400, 400);
	playerDeathSprite4.setPosition(400, 400);
	playerDeathSprite5.setPosition(400, 400);
	playerDeathSprite6.setPosition(400, 400);
	playerDeathSprite7.setPosition(400, 400);
	playerDeathSprite8.setPosition(400, 400);
	playerDeathSprite9.setPosition(400, 400);
	playerDeathSprite10.setPosition(400, 400);
	playerDeathSprite11.setPosition(400, 400);
	playerDeathSprite12.setPosition(400, 400);
}

int GameOverScreen::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	sf::Font font;
	int gameOverTimer = 2500; // Made so that the user would not instantly close the game over screen
	int gifTimer = 1800; // used to determine which sprite is currently displayed
	isRunning = true;
	
	if (!font.loadFromFile("Xeron.ttf"))
		return -1;

	sf::Text gameOver;
	sf::Text score;

	int finalScore = points; // gotten from the points.h to display points received in the gameScreen.hpp file

	gameOver.setFont(font);
	gameOver.setColor(sf::Color::Red);
	gameOver.setCharacterSize(80);
	gameOver.setString("Game Over");
	gameOver.setPosition(80, 100);

	score.setFont(font);
	score.setColor(sf::Color::White);
	score.setCharacterSize(40);
	score.setString("Score: " + to_string(finalScore));
	score.setPosition(150, 300);

	while (isRunning)
	{
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed) // closes the program if the user presses the x button
			{
				return -1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && gameOverTimer < 0) // closes the program is the user pressed enter after a few seconds
			{
					isRunning = false;
			}
		}

		gifTimer--;
		gameOverTimer--;

		App.clear();

		// Creates the pseudo gif by displaying a different sprite once each condition is met
		if (gifTimer > 1650)
			App.draw(playerDeathSprite1);
		else if (gifTimer > 1500)
			App.draw(playerDeathSprite2);
		else if (gifTimer > 1350)
			App.draw(playerDeathSprite3);
		else if (gifTimer > 1200)
			App.draw(playerDeathSprite4);
		else if (gifTimer > 1050)
			App.draw(playerDeathSprite5);
		else if (gifTimer > 900)
			App.draw(playerDeathSprite6);
		else if (gifTimer > 750)
			App.draw(playerDeathSprite7);
		else if (gifTimer > 600)
			App.draw(playerDeathSprite8);
		else if (gifTimer > 450)
			App.draw(playerDeathSprite9);
		else if (gifTimer > 300)
			App.draw(playerDeathSprite10);
		else if (gifTimer > 150)
			App.draw(playerDeathSprite11);
		else if (gifTimer > 0)
			App.draw(playerDeathSprite12);
		
		App.draw(score);

		App.draw(gameOver);

		App.display();
	}

	return -1;


}