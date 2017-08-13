#pragma once
#include <SFML/Audio.hpp>
#include "Actor.h"

class Player : public Actor
{
public:
	Player(sf::Vector2f startingPosition, std::string textureFilePath);
	~Player();

	// Takes a coordinate to shoot, returns true if shot fired
	bool shoot(sf::Vector2f shotCoordinates);

	// How much ammo the player has remaining
	int getAmmo(); 

private:
	int ammo = 20; // Starting ammo

	sf::SoundBuffer shotSoundBuffer;
	sf::Sound shotSound;
	//sf::SoundBuffer reloadingSoundBuffer;
	//sf::Sound reloadingSound;

	sf::Clock shotClock;
};

