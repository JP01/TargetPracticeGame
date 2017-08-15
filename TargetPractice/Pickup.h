#pragma once
#include "Actor.h"

class Pickup : public Actor
{
public:
	Pickup(sf::Vector2f startingPosition, std::string textureFilePath);
	~Pickup();
};

