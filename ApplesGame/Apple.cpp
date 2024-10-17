#include "Apple.h"
namespace ApplesGame
{
	void Apple::Initialization(float sizeGameObject, Position2D positionGameObject, sf::Texture gameObjectTexture)
	{
		position = positionGameObject;
		size = sizeGameObject;
		texture = gameObjectTexture;
		Spawn(position);
	}

	float Apple::GetAcceleration()
	{
		return forceAcceleration;
	}

	void Apple::Draw(sf::RenderWindow& window)
	{
			if (isItemPicked == false)
			{
				window.draw(sprite);
			}
	}
}