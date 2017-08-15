#include "Pickup.h"
#include <iostream>


Pickup::Pickup(sf::Vector2f startingPosition, std::string textureFilePath)
	: Actor(startingPosition, textureFilePath)
{
	std::cout <<
		"Spawning a new pickup at location ("
		<< startingPosition.x << ", " << startingPosition.y << ")."
		<< std::endl;

}


Pickup::~Pickup()
{
}
