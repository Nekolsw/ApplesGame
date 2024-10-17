#pragma once
#include <cassert>
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ApplesGame 
{
	struct GameResources {
		sf::Texture playerTexture, appleTexture, rockTexture, plugTexture;
		sf::SoundBuffer appleEat, playerDeath;
		sf::Font fontText;
	};

	void InitializingResources(GameResources& resources);

	
}