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

	// Current player ammo
	int getAmmo(); 
	
	// Set player ammo
	void setAmmo(int ammo);

	// Current player health
	int getHealth();

	// Reduce the players health by 10
	void damage();

	// Current player score
	int getScore();

	// Set the player score
	void setScore(int score);

private:
	int mAmmo = 20; // Starting ammo
	int mHealth = 100; // Starting health
	int mScore = 0; // Starting score

	float fireRate = 0.2; // Time between each shot

	sf::SoundBuffer shotSoundBuffer;
	sf::Sound shotSound;
	sf::SoundBuffer reloadingSoundBuffer;
	sf::Sound reloadingSound;

	sf::Clock shotClock;
};

