#include "Engine.h"
#include <iostream>


Engine::Engine(sf::Vector2f windowResolution)
	: mBackgroundTextureFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/map2.png")
	, playerTextureFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/player.png")
	, botTextureFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/bot.png")
	, mWindowResX(windowResolution.x)
	, mWindowResY(windowResolution.y)
	, playerStartingPosition(sf::Vector2f(mWindowResX * 0.50, mWindowResY * 0.90))
	, player(playerStartingPosition, playerTextureFilepath)
	, mPlayArea(sf::Vector2f(mWindowResX * 0.83, mWindowResY * 0.15)) // Size of the play area
	, score(0)
{
	// Setup the game window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	mWindow.create(
		sf::VideoMode(mWindowResX, mWindowResY),
		"Target Practice",
		sf::Style::Default,
		settings);
	mWindow.setFramerateLimit(60); // Set the frame limit so that we don't overload CPU needlessly
	
	// Add a background
	mBackgroundTexture.loadFromFile(mBackgroundTextureFilepath);
	mBackgroundSprite.setTexture(mBackgroundTexture);

	// Position and initialise the ammo and score counters
	font.loadFromFile("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/arial.ttf");
	ammoText.setFont(font);
	ammoText.setPosition(sf::Vector2f(mWindowResX * 0.80, mWindowResY * 0.95));
	ammoText.setCharacterSize(24);
	ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(mWindowResX * 0.80, mWindowResY * 0.05));
	scoreText.setCharacterSize(24);
	ammoText.setString("Score: " + std::to_string(player.getAmmo()));

	// Position the play area
	mPlayArea.setPosition(sf::Vector2f(mWindowResX * 0.10, mWindowResY * 0.80));
	mPlayAreaTopLeft = mPlayArea.getTransform().transformPoint(sf::Vector2f(0, 0));
	mPlayAreaTopRight = mPlayArea.getTransform().transformPoint(sf::Vector2f(mPlayArea.getSize().x, 0));
	mPlayAreaBottomRight = mPlayArea.getTransform().transformPoint(sf::Vector2f(0, mPlayArea.getSize().y));
	mPlayAreaBottomLeft = mPlayArea.getTransform().transformPoint(sf::Vector2f(mPlayArea.getSize().x, mPlayArea.getSize().y));

	// Spawn some bots
	srand(time(0));
	bots.push_back(spawnNewBot());
	bots.push_back(spawnNewBot());
	bots.push_back(spawnNewBot());
	bots.push_back(spawnNewBot());
	bots.push_back(spawnNewBot());
}


void Engine::start()
{
	// Timer setup
	sf::Clock clock;
	

	while (mWindow.isOpen())
	{
		// Restart the clock and save elapsed time to dt
		sf::Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();

		sf::Event windowEvent;
		while (mWindow.pollEvent(windowEvent))
		{
			if (sf::Event::Closed)
				mWindow.close();
		}

		inputHandler();
		update(dtAsSeconds);
		draw();
	}

}

sf::Vector2f Engine::randomBotLocation()
{
	// Create a new bot at a random location off the top of the screen
	float minX = mWindowResX * 0.20;
	float maxX = mWindowResX * 0.80;
	float minY = -mWindowResY * 0.10;
	float maxY = -mWindowResY * 1.00;

	float randX = (int)(mWindowResX * 1 / (rand() % (int)9 + 1.1));
	float randY = (int)(-mWindowResY * 1 / (rand() % (int)9 + 1.1));

	return sf::Vector2f(randX, randY);
}

std::unique_ptr<Bot> Engine::spawnNewBot()
{
	return std::unique_ptr<Bot>(new Bot(randomBotLocation(), botTextureFilepath));
}



void Engine::inputHandler()
{
	// Handle the player quitting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		mWindow.close();
	
	// Handle player character actions
	mouseHandler();
	keyboardHandler();
}


void Engine::keyboardHandler()
{	
	// Collision detection here is dirty, until SFML has some nicer way to handle collision this will do
	// Handle input and window boundary collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player.moveLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player.moveRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player.moveUp();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player.moveDown();

	// If the movement puts the player outside the playzone then reset
	if (player.getPosition().x < mPlayAreaTopLeft.x)
		player.moveRight();
	if (player.getPosition().x > mPlayAreaTopRight.x)
		player.moveLeft();
	if (player.getPosition().y < mPlayAreaTopLeft.y)
		player.moveDown();
	if (player.getPosition().y > mPlayAreaBottomRight.y)
		player.moveUp();
}


void Engine::mouseHandler()
{
	// If gamestate is active
	sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition(mWindow);

	// If mouse is within the window bounds then act
	player.aimAt(mousePosition);
	// Handle shotting
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (player.shoot(mousePosition))
		{
			// Check for hits
			for (auto& bot : bots) {
				if (bot->getBoundingBox().contains(mousePosition)) {
					// Replace this bot with a new one
					bot = spawnNewBot();
					score++;
					std::cout << "bot hit" << std::endl;
				}
			}
		}
	}
}


void Engine::botMover()
{
	for (auto &bot : bots)
	{
		bot->setSpeed(200.0);
		bot->moveDown();
		if (bot->getPosition().y > mWindowResY * 0.70) {
			// Bot attacks player, remove health and reset
			bot->resetPosition();
		}
	}
}


void Engine::update(float dtAsSeconds)
{
	// Update actor posititions
	botMover();
	player.update(dtAsSeconds);
	for (auto &bot : bots)
		bot->update(dtAsSeconds);

	// Update text fields
	ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
	scoreText.setString("Score: " + std::to_string(score));
}


void Engine::draw()
{
	// Clear the last frame
	mWindow.clear();

	// Draw the assets
	mWindow.draw(mBackgroundSprite);
	mWindow.draw(player.getSprite());

	for (auto &bot : bots)
		mWindow.draw(bot->getSprite());

	// Draw ammo and score
	mWindow.draw(ammoText);
	mWindow.draw(scoreText);

	// Display the scene
	mWindow.display();
}


Engine::~Engine()
{
}