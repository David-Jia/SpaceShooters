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

	Screen_0 s0;

	Screens.push_back(&s0);

	Screen_1 s1;

	Screens.push_back(&s1);

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return EXIT_SUCCESS;
}