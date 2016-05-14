#include "SFML/Graphics.hpp"

using namespace std;

class Player
{
	private:
		sf::Sprite playerSprite;
		sf::Texture playerTexture;
		int lives;
		
	public:
		// Constructors
		Player();
		Player(int nothing);
		// Getters
		sf::Sprite& getSprite();
		int getLives();
		// Other Methods
		void removeLife();

};

Player::Player()
{
	playerTexture.loadFromFile("Images/Player.png");
	playerSprite.setTexture(playerTexture, true);
	lives = 3;
}

sf::Sprite& Player::getSprite()
{
	return playerSprite;
}

int Player::getLives()
{
	return lives;
}

void Player::removeLife()
{
	lives--;
}

