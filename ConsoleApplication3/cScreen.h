// Allows multiple screens and also ensures that they are able to run with each other and not cause conflicts by interfering with each other
// It is a virtual object 

#ifndef C_SCREEN_INCLUDED
#define C_SCREEN_INCLUDED
#include <SFML/Graphics.hpp>

class CScreen
{
	public:
		virtual int Run(sf::RenderWindow &App) = 0;
};

#endif // C_SCREEN_INCLUDED