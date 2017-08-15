#include "Player.h"


Player::Player(sf::Vector2f startingPosition, std::string textureFilePath)
	: Actor(startingPosition, textureFilePath)
{
	setSpriteOrigin(sf::Vector2f(83, 25)); // Coordinate location of origin on sprite

	if (shotSoundBuffer.loadFromFile("../Resources/shot.wav")) {
		shotSound.setBuffer(shotSoundBuffer);
	}
	if (reloadingSoundBuffer.loadFromFile("../Resources/reload.wav")) {
		reloadingSound.setBuffer(reloadingSoundBuffer);
	}
}


bool Player::shoot(sf::Vector2f shotCoordinates)
{
	float elapsedTimeAsSeconds = shotClock.getElapsedTime().asSeconds();
	if (elapsedTimeAsSeconds >= 0.3 && mAmmo > 0) { // weapon fire rate
		// Trigger sound / visual effects
		shotSound.play();
		// wait until another shot is able to be fired 
		shotClock.restart();
		mAmmo--;
		return true;
	}
	return false;
}


int Player::getAmmo()
{
	return mAmmo;
}


int Player::getHealth()
{
	return mHealth;
}


void Player::damage()
{
	mHealth -= 10;
	if (mHealth < 0)
		mHealth = 0;
}


int Player::getScore()
{
	return mScore;
}


void Player::setScore(int score)
{
	mScore = score;
}


void Player::setAmmo(int ammo)
{
	reloadingSound.play();
	mAmmo = ammo;
}

Player::~Player()
{
}
