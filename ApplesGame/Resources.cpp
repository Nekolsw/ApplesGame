#include "Resources.h"

namespace ApplesGame
{
	void InitializingResources(GameResources& resources)
	{
		//Load image
		assert(resources.playerTexture.loadFromFile(RESOURCES_PATH + "player.png"));
		assert(resources.appleTexture.loadFromFile(RESOURCES_PATH + "apple.png"));
		assert(resources.rockTexture.loadFromFile(RESOURCES_PATH + "rock.png"));
		assert(resources.plugTexture.loadFromFile(RESOURCES_PATH + "plug.png"));

		//Load font
		assert(resources.fontText.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Bold.ttf"));

		//Load sound
		assert(resources.appleEat.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(resources.playerDeath.loadFromFile(RESOURCES_PATH + "Death.wav"));
	}




}