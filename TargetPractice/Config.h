#pragma once
#include <SFML/Graphics.hpp>

namespace Config
{
	const float WINDOW_WIDTH = 800;
	const float WINDOW_HEIGHT = 600;

	// Arial font filepath
	const std::string ARIAL_FONT = "../Resources/arial.ttf";

	// Background texture filepath
	const std::string BG_TX_FILEPATH = "../Resources/map2.png";

	// Player texture filepath
	const std::string PLAYER_TX_FILEPATH = "../Resources/player.png";

	// Bot texture filepath
	const std::string BOT_TX_FILEPATH = "../Resources/bot.png";

	// Ammo texture filepath
	const std::string AMMO_TX_FILEPATH = "../Resources/ammo.png";

	// Gunshot sound filepath
	const std::string GUNSHOT_SND_FILEPATH = "../Resources/shot.wav";

	// Reload sound filepath
	const std::string RELOAD_SND_FILEPATH = "../Resources/reload.wav";

	// Main soundtrack
	const std::string THEME_MUS_FILEPATH = "../Resources/TPOST.ogg";
}
