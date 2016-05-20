#include <iostream>
#include <SFML/Graphics.hpp>
#include "screens.hpp"
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	vector<CScreen*> Screens; // creates a vector of the screens that would be run

	int screen = 0; // starts the screen at 0

	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Space Shooters");

	// Plays the first screen, then the second screen, and finally the third screen
	StartScreen s0;

	Screens.push_back(&s0);

	GameScreen s1;

	Screens.push_back(&s1);

	GameOverScreen s2;

	Screens.push_back(&s2);

	while (screen >= 0) // makes sure that each screen is run and the game does not abruptly end early
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}