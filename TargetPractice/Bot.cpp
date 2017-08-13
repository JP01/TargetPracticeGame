#include "Bot.h"
#include <iostream>

Bot::Bot(sf::Vector2f startingPosition, std::string textureFilePath)
	: Actor(startingPosition, textureFilePath)
{
	std::cout << 
		"Spawning a new bot at location ("
		<< startingPosition.x << ", " << startingPosition.y << ")." 
		<< std::endl;
}



Bot::~Bot()
{
}
