#pragma once
#include "Actor.h"

class Bot : public Actor
{
public:
	Bot(sf::Vector2f startingPosition, std::string textureFilePath);
	~Bot();
};

