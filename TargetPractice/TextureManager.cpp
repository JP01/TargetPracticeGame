#include <assert.h>
#include "TextureManager.h"

TextureManager* TextureManager::m_s_Instance = nullptr;

TextureManager::TextureManager()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureManager::getTexture(std::string const& filepath)
{
	// Get a reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance->m_Textures;

	// Create an iterator of key-value-pair search for a match
	auto keyValuePair = m.find(filepath);

	if (keyValuePair != m.end())
	{
		// match! Return the value
		return keyValuePair->second;
	}
	// No current texture match, create a new k-v-p using the filename & load
	auto& texture = m[filepath];
	texture.loadFromFile(filepath);
	return texture;
}