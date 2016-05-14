#include "cScreen.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class StartScreen : public CScreen
{
private:
	bool isRunning;

public:
	StartScreen(void);
	virtual int Run(sf::RenderWindow &App);
};

StartScreen::StartScreen(void)
{
	isRunning = false;
}

int StartScreen::Run(sf::RenderWindow &App)
{
	sf::Event Event;
	isRunning = true;
	sf::Font font;
	sf::Text title;
	sf::Text start;

	if (!font.loadFromFile("Xeron.ttf"))
		return -1;

	title.setFont(font);
	title.setColor(sf::Color::White);
	title.setCharacterSize(48);
	title.setString("Space Shooters");
	title.setPosition(110, 100);

	start.setFont(font);
	start.setColor(sf::Color::White);
	start.setCharacterSize(24);
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
					isRunning = false;
			}
		}

		App.clear();

		App.draw(title);
		App.draw(start);

		App.display();
	}
	return 1;
}
