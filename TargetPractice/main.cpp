#pragma once
#include "SFML/sfml.h"
#include "Engine.h"


int main()
{
	Engine engine(sf::Vector2f(800, 600));
	engine.start();
	return 0;
}