#pragma once
#include "SFML/sfml.h"
#include "GameConfiguration.h"
#include "Engine.h"


int main()
{
	Engine engine(
		sf::Vector2f(
			GameConfiguration::WINDOW_WIDTH,
			GameConfiguration::WINDOW_HEIGHT));

	engine.start();
	return 0;
}