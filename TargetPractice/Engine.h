#pragma once
#include <random>
#include <thread>   
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bot.h"

class Engine
{
public:
	// Construction
	Engine(sf::Vector2f windowResolution);
	~Engine();

	// start the game engine
	void start();

private:
	// Rendering window
	sf::RenderWindow mWindow;
	int mWindowResX;
	int mWindowResY;

	// Background
	sf::Sprite mBackgroundSprite;
	sf::Texture mBackgroundTexture;
	std::string mBackgroundTextureFilepath;

	// Score
	int score;
	sf::Font font;
	sf::Text ammoText;
	sf::Text scoreText;

	// Player
	sf::Vector2f playerStartingPosition;
	std::string playerTextureFilepath;
	Player player;

	// Bots
	std::string botTextureFilepath;
	std::vector<std::unique_ptr<Bot>> bots;
	void botMover();
	// Generate a random location at the top of the screen for bots to spawn
	sf::Vector2f randomBotLocation();

	// Spawn a new bot in a random location off the top of the screen
	std::unique_ptr<Bot> spawnNewBot();

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

