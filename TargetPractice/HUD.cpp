#include <iostream>
#include "Config.h"
#include "HUD.h"

HUD::HUD(Player& _player)
	: player(_player)
{
	sf::Vector2u windowRes;
	windowRes.x = Config::WINDOW_WIDTH;
	windowRes.y = Config::WINDOW_HEIGHT;

	std::cout << "Windowsize = (" << windowRes.x << ", " << windowRes.y << ")." << std::endl;

	// Position the HUD elements
	arialFont.loadFromFile(Config::ARIAL_FONT);
	ammoText.setFont(arialFont);
	ammoText.setPosition(sf::Vector2f(windowRes.x * 0.80, windowRes.y * 0.95));
	ammoText.setCharacterSize(24);

	scoreText.setFont(arialFont);
	scoreText.setPosition(sf::Vector2f(windowRes.x * 0.80, windowRes.y * 0.05));
	scoreText.setCharacterSize(24);

	healthText.setFont(arialFont);
	healthText.setPosition(sf::Vector2f(windowRes.x  * 0.80, windowRes.y * 0.90));
	healthText.setCharacterSize(24);

	ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
	scoreText.setString("Score: " + std::to_string(player.getScore()));
	healthText.setString("Health: " + std::to_string(player.getHealth()));
	gameOverText.setString("Score: " + std::to_string(player.getScore()) + "\n    Hit Esc");

	gameOverText.setFont(arialFont);
	gameOverText.setCharacterSize(56);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
	gameOverText.setPosition(windowRes.x * 0.50, windowRes.y * 0.5);
}


sf::Text HUD::getScoreText()
{
	return scoreText;
}


sf::Text HUD::getAmmoText()
{
	return ammoText;
}


sf::Text HUD::getHealthText()
{
	return healthText;
}

sf::Text HUD::getGameOverText()
{
	return gameOverText;
}


void HUD::update(float dtAsSeconds)
{
	ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
	scoreText.setString("Score: " + std::to_string(player.getScore()));
	healthText.setString("Health: " + std::to_string(player.getHealth()));
	gameOverText.setString("Score: " + std::to_string(player.getScore()) + "\nHit Esc");
}
