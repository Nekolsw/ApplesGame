#pragma once
#include "PickupItem.h"
namespace ApplesGame
{
	class Apple : public PickupItem 
	{
	private:
		const float forceAcceleration = 20.f;
	public:
		void Draw(sf::RenderWindow& window) override;
		void Initialization(float sizeGameObject, Position2D positionGameObject, sf::Texture gameObjectTexture) override;
		float GetAcceleration();
	};

}