#include <iostream>
#include <SFML/Graphics.hpp>
#include "screens.hpp"
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	vector<CScreen*> Screens;

	int screen = 0;

	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Space Shooters");

	StartScreen s0;

	Screens.push_back(&s0);

	GameScreen s1;

	Screens.push_back(&s1);

	GameOverScreen s2;

	Screens.push_back(&s2);

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}