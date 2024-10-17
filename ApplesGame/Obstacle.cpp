#include "Obstacle.h"
namespace ApplesGame
{
	void Obstacle::Spawn(Position2D GameObjectPosition)
	{
		position = GameObjectPosition;
		sprite.setTexture(texture);
		SetSpriteSize(sprite, size, size);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		sprite.setPosition({ position.x, position.y });
	}

}
