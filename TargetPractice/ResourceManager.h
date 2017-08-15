#pragma once
#include <map>
#include <memory>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	sf::Texture getBackgroundTexture();
	sf::Texture getPlayerTexture();
	sf::Texture getBotTexture();
	sf::Sound getGunshotSound();
	sf::Font getMainFont();

private:
	enum GameTexture
	{
		Background,
		Player,
		Bot
	};

	enum GameSound
	{
		Gunshot,
		Reload
	};

	enum GameFont
	{
		Arial
	};

	std::string mBackgroundTextureFilepath;
	std::string playerTextureFilepath;
	std::string botTextureFilepath;
	std::string gunshotSoundFilepath;
	//std::string reloadSoundFilepath;
	std::string fontFilepath;

	sf::Texture background;
	sf::Texture player;
	sf::Texture bot;

	sf::SoundBuffer gunshotBuffer;
	sf::Sound gunshotSound;

	sf::Font fontArial;

	//std::map<GameTexture, sf::Texture> textures;
	//std::map<GameSound, sf::Sound> sounds;
	//std::map<GameFont, sf::Font> fonts;
};

