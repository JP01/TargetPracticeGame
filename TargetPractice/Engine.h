#pragma once
#include <random>
#include <thread>   
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Pickup.h"
#include "Player.h"
#include "Bot.h"
#include "HUD.h"
#include "ParticleSystem.h"

class Engine
{
public:
	// Construction
	Engine(sf::Vector2f windowResolution);
	~Engine();

	// start the game engine
	void start();

private:
	// Texturing
	TextureManager tm;

	// Rendering window
	sf::RenderWindow mWindow;
	int mWindowResX;
	int mWindowResY;

	// HUD
	HUD hud;

	// Background
	sf::Sprite mBackgroundSprite;

	// Player
	sf::Vector2f playerStartingPosition;
	Player player;
	int mBotKills; // The number of bots killed by the player this round
	int ammoCratesLooted; // The number of ammo crates the player has picked up

	// Bots
	std::vector<std::unique_ptr<Bot>> bots;
	void botMover();
	
	// Generate a random location within the area
	sf::Vector2f randomLocation(sf::FloatRect area);

	// Spawn a new bot in a random location off the top of the screen
	std::unique_ptr<Bot> spawnNewBot();

	// Pickups
	std::vector<std::unique_ptr<Pickup>> pickups;
	std::unique_ptr<Pickup> spawnNewPickup();

	// Handle input
	void inputHandler();
	void keyboardHandler();
	void mouseHandler();

	// Area in which the player is allow to move
	sf::RectangleShape mPlayArea;
	sf::Vector2f mPlayAreaTopLeft;
	sf::Vector2f mPlayAreaTopRight;
	sf::Vector2f mPlayAreaBottomRight;
	sf::Vector2f mPlayAreaBottomLeft;

	// Update all game logic
	void update(float dtAsSeconds);

	// Render the scene
	void draw();
};

