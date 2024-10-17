#include "Rock.h"
namespace ApplesGame
{
	void Rock::Initialization(float sizeGameObject, Position2D positionGameObject, sf::Texture gameObjectTexture)
	{
		position = positionGameObject;
		size = sizeGameObject;
		texture = gameObjectTexture;
		Spawn(position);
	}

	void Rock::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

}