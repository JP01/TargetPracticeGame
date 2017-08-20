#pragma once
#include <SFML/sfml.h>
#include "Config.h"
#include "Engine.h"


int main()
{
	Engine engine(
		sf::Vector2f(
			Config::WINDOW_WIDTH,
			Config::WINDOW_HEIGHT));

	engine.start();
	return 0;
}