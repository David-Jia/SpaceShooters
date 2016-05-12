#include "SFML/Graphics.hpp"

using namespace std;

class Player{
	private:
		sf::Sprite playerSprite;
		sf::Texture playerTexture;
		
	public:
		Player();
		sf::Sprite& getSprite();
};

Player::Player()
{
	playerTexture.loadFromFile("Images/Player.png");
	playerSprite.setTexture(playerTexture, true);
}

sf::Sprite& Player::getSprite()
{
	return playerSprite;
}