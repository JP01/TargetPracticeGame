#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

/*
	This class provides a GUI for the referenced player
*/

class HUD
{
public:
	HUD(Player& player);
	sf::Text getScoreText();
	sf::Text getAmmoText();
	sf::Text getHealthText();
	sf::Text getGameOverText();

	// Update the HUD elements
	void update(float dtAsSeconds);

private:
	// Reference to the player who's HUD we are displaying
	Player& player;

	sf::Font arialFont;
	sf::Text scoreText;
	sf::Text ammoText;
	sf::Text healthText;
	sf::Text gameOverText;

};