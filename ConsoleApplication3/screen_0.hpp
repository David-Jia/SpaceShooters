#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

class Screen_0 : public CScreen
{
private:
	bool isPlaying;

public:
	Screen_0(void);
	virtual int Run(sf::RenderWindow &App);
};

Screen_0::Screen_0(void)
{
	isPlaying = false;
}

int Screen_0::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	bool isRunning = true;
	sf::Font font;
	sf::Text title;
	sf::Text start;
	int menu = 0;

	if (!font.loadFromFile("Xeron.ttf"))
		return -1;

	title.setFont(font);
	title.setColor(sf::Color::White);
	title.setCharacterSize(64);
	title.setString("Space Shooters");
	title.setPosition(200, 100);

	start.setFont(font);
	start.setColor(sf::Color::White);
	start.setCharacterSize(32);
	start.setString("Press enter to start");
	start.setPosition(200, 400);

	while (isRunning)
	{
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				return -1;
			}

			if (Event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::Return)
				{
					isPlaying = true;
				}

				/*else
				{
				return -1;
				}*/
			}
		}

		App.clear();

		App.draw(title);
		App.draw(start);

		App.display();
	}
	return 0;
}
