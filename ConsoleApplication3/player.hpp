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
		// Summary: Reduces the number of lives the player object has by 1
		// Precondition: A player class object needs to call this function
		// Postcondition: The player class object that called this function has it's lives attribute decreased by 1

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

