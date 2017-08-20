#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class TextureManager
{
public:
	TextureManager();
	static sf::Texture& getTexture(std::string const& filepath);

private:
	// A map that holds pairs of strings and textures
	std::map<std::string, sf::Texture> m_Textures;

	// A pointer to the class instance
	static TextureManager* m_s_Instance;
};

