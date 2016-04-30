#include "SFML/Graphics.hpp"

int main(int argc, char** argv){
	sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Hello Cruel World");

	sf::Event event;

	sf::Font font;
	if (!font.loadFromFile("xeron.ttf"))
		return 42;

	sf::Text text("Space Shooters", font, 64);
	text.setColor(sf::Color::White);

	sf::FloatRect bounds(text.getLocalBounds());
	text.setPosition(renderWindow.getSize().x / 2 - (bounds.left + bounds.width / 2),
		renderWindow.getSize().y / 2 - (bounds.top + bounds.height / 2));

	while (renderWindow.isOpen()){
		while (renderWindow.pollEvent(event)){
			if (event.type == sf::Event::EventType::Closed){
				renderWindow.close();
			}
		}

		renderWindow.clear(sf::Color::Black);
		renderWindow.draw(text);
		renderWindow.display();
	}
}