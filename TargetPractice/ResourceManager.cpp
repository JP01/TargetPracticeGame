#include "ResourceManager.h"


ResourceManager::ResourceManager()
	: mBackgroundTextureFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/map2.png")
	, playerTextureFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/player.png")
	, botTextureFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/bot.png")
	, gunshotSoundFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/shot.wav")
	, fontFilepath("F:/Users/the_m/Documents/Code Practice/SFML_GAMES/TargetPractice/Resources/arial.ttf")
{

	if (!background.loadFromFile(mBackgroundTextureFilepath))
		throw std::runtime_error("map2.png - Failed to load ");

	if (!player.loadFromFile(playerTextureFilepath))
		throw std::runtime_error("player.png - Failed to load ");

	if (!bot.loadFromFile(botTextureFilepath))
		throw std::runtime_error("bot.png - Failed to load ");

	if (!gunshotBuffer.loadFromFile(gunshotSoundFilepath)) {
		throw std::runtime_error("bot.png - Failed to load ");
	} else {
		gunshotSound.setBuffer(gunshotBuffer);
	}

	if (!fontArial.loadFromFile(fontFilepath))
		throw std::runtime_error("arial.ttf - Failed to load ");
}


sf::Texture ResourceManager::getBackgroundTexture()
{
	return background;
}


sf::Texture ResourceManager::getPlayerTexture()
{
	return player;
}


sf::Texture ResourceManager::getBotTexture()
{
	return bot;
}

sf::Sound ResourceManager::getGunshotSound()
{
	return gunshotSound;
}


sf::Font ResourceManager::getMainFont()
{
	return fontArial;
}


ResourceManager::~ResourceManager()
{
}
