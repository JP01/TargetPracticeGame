#include "Player.h"


Player::Player(sf::Vector2f startingPosition, std::string textureFilePath)
	: Actor(startingPosition, textureFilePath)
{
	setSpriteOrigin(sf::Vector2f(83, 25)); // Coordinate location of origin on sprite

	if (shotSoundBuffer.loadFromFile("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/shot.wav")) {
		shotSound.setBuffer(shotSoundBuffer);
	}
	/*if (!reloadingSoundBuffer.loadFromFile("reloading.wav")) {
		reloadingSound.setBuffer(reloadingSoundBuffer);
	}*/
}


bool Player::shoot(sf::Vector2f shotCoordinates)
{
	float elapsedTimeAsSeconds = shotClock.getElapsedTime().asSeconds();
	if (elapsedTimeAsSeconds >= 0.3 && ammo > 0) { // weapon fire rate
		// Trigger sound / visual effects
		shotSound.play();
		// wait until another shot is able to be fired 
		shotClock.restart();
		ammo--;
		return true;
	}
	return false;
}


int Player::getAmmo()
{
	return ammo;
}

Player::~Player()
{
}
