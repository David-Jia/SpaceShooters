// Allows multiple screens and also ensures that they are able to run with each other and not cause conflicts by interfering with each other
// It is a virtual purely class

#ifndef C_SCREEN_INCLUDED
#define C_SCREEN_INCLUDED
#include <SFML/Graphics.hpp>

class CScreen
{
	public:
		virtual int Run(sf::RenderWindow &App) = 0;
		// Summary: This function runs the event that appear in the screen
		// Precondition: Takes in a number that determines which virtual Run class will run
		// Postcondition: The screen number that corresponds with the input will run
};

#endif // C_SCREEN_INCLUDED