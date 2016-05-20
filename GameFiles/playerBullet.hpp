#include "SFML/Graphics.hpp"

using namespace std;

class PlayerBullet
{
	private:
		sf::Sprite playerBulletSprite;
		sf::Texture playerBulletTexture;
		bool bulletPresent; // is true if the bullet is active on screen
		
	public:
		//Constructors
		PlayerBullet();
		//Getters
		sf::Sprite& getSprite();
		bool getBulletPresent() const {return bulletPresent;}
		//Setters 
		void setBulletPresent(bool present);
};

PlayerBullet::PlayerBullet()
{
	playerBulletTexture.loadFromFile("Images/PlayerBullet.png");
	playerBulletSprite.setTexture(playerBulletTexture, true);
	bulletPresent = true;
}
						
sf::Sprite& PlayerBullet::getSprite()
{
	return playerBulletSprite;
}

void PlayerBullet::setBulletPresent(bool present)
{
	bulletPresent = present;
}
