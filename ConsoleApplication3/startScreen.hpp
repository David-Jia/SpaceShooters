// Title screen, the first screen that is displayed
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
	// Summary: This function runs the event that appear in the screen
	// Precondition: Takes in a number that determines which virtual Run class will run
	// Postcondition: The screen number that corresponds with the input will run
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

	// Sets and error checks that the font that will be used loaded in correctly
	if (!font.loadFromFile("Xeron.ttf"))
		return -1;

	// title and starts correspond to the text that will appear in the main screen
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
			if (Event.type == sf::Event::Closed) // closes the program if the user presses the x button
			{
				return -1;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) // Exits the loop and returns the number of the next screen
			{
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
