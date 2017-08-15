#include "Engine.h"
#include <iostream>


Engine::Engine(sf::Vector2f windowResolution)
	: mBackgroundTextureFilepath("../Resources/map2.png")
	, playerTextureFilepath("../Resources/player.png")
	, botTextureFilepath("../Resources/bot.png")
	, ammoTextureFilepath("../Resources/ammo.png")
	, mWindowResX(windowResolution.x)
	, mWindowResY(windowResolution.y)
	, playerStartingPosition(sf::Vector2f(mWindowResX * 0.50, mWindowResY * 0.90))
	, player(playerStartingPosition, playerTextureFilepath)
	, mPlayArea(sf::Vector2f(mWindowResX * 0.83, mWindowResY * 0.15)) // Size of the play area
	, hud(player)
{
	// Setup the game window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	mWindow.create(
		sf::VideoMode(mWindowResX, mWindowResY),
		"Target Practice",
		sf::Style::Default,
		settings);
	mWindow.setFramerateLimit(120); // Set the frame limit so that we don't overload CPU needlessly
	
	// Add a background
	mBackgroundSprite.setTexture(tm.getTexture(mBackgroundTextureFilepath));

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
		// Handle the player quitting
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			mWindow.close();

		if (player.getHealth() > 0) {
			inputHandler();
			update(dtAsSeconds);
		}
		draw();
	}

}

sf::Vector2f Engine::randomLocation(sf::FloatRect area)
{

	int minX = area.left;
	int minY = area.top;
	int maxX = area.left + area.width;
	int maxY = area.top + area.height;

	// Generate a random point within the box
	int randX = rand() % (maxX - minX + 1) + minX;
	int randY = rand() % (maxY - minY + 1) + minY;
	return sf::Vector2f(randX, randY);
}


std::unique_ptr<Bot> Engine::spawnNewBot()
{
	sf::FloatRect spawnArea;
	spawnArea.left = mWindowResX * 0.20;
	spawnArea.top = -mWindowResY * 1.00;

	spawnArea.width = mWindowResX * 0.60;
	spawnArea.height = mWindowResY * 0.5;

	return std::unique_ptr<Bot>(new Bot(randomLocation(spawnArea), botTextureFilepath));
}


std::unique_ptr<Pickup> Engine::spawnNewPickup()
{
	sf::FloatRect spawnArea;
	spawnArea.left = mPlayAreaTopLeft.x;
	spawnArea.top = mPlayAreaTopLeft.y;

	spawnArea.width = mPlayArea.getSize().x;
	spawnArea.height = mPlayArea.getSize().y - 40.0; // minus 40 to make sure it doesn't spawn too low on the screen 
	return std::unique_ptr<Pickup>(new Pickup(randomLocation(spawnArea), ammoTextureFilepath));
}


void Engine::inputHandler()
{
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
					int newScore = player.getScore();
					player.setScore(++newScore);
					std::cout << "bot hit" << std::endl;
				}
			}
		}
	}
}


void Engine::botMover()
{
	// Bot speed increases by 1% every time player scores
	float botSpeed = 150 * (1 + (player.getScore() / 100.0));

	for (auto &bot : bots)
	{
		bot->setSpeed(botSpeed);
		bot->moveDown();
		if (bot->getPosition().y > mWindowResY * 0.70) {
			// Bot attacks player, remove health and reset
			player.damage();
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
	hud.update(dtAsSeconds);
	
	// If 10 bots have been killed spawn some ammo
	if ((player.getScore() > 0) && (player.getScore() % 10 == 0))
	{
		if (pickups.size() == 0) {
			pickups.push_back(spawnNewPickup());
		}
	}

	bool ammoGot = false;
	for (auto &pickup : pickups) {
		pickup->update(dtAsSeconds);
		if (pickup->getBoundingBox().contains(player.getPosition()))
		{
			int currentAmmo = player.getAmmo();
			currentAmmo += 15;
			player.setAmmo(currentAmmo);
			ammoGot = true;
			int score = player.getScore();
			player.setScore(++score);
		}
	}
	if (ammoGot)
		pickups.pop_back();

}


void Engine::draw()
{
	// Clear the last frame
	mWindow.clear();

	// Draw the assets
	mWindow.draw(mBackgroundSprite);

	for (auto &bot : bots)
		mWindow.draw(bot->getSprite());

	for (auto &pickup : pickups)
		mWindow.draw(pickup->getSprite());

	mWindow.draw(player.getSprite());

	if (player.getHealth() > 0) {
		// Draw ammo and score
		mWindow.draw(hud.getAmmoText());
		mWindow.draw(hud.getScoreText());
		mWindow.draw(hud.getHealthText());
	}
	else {
		mWindow.draw(hud.getGameOverText());
	}

	// Display the scene
	mWindow.display();
}


Engine::~Engine()
{
}