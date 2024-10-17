#pragma once
#include "Obstacle.h"
namespace ApplesGame
{
	class Rock : public Obstacle
	{
	public:
		void Draw(sf::RenderWindow& window) override;
		void Initialization(float sizeGameObject, Position2D positionGameObject, sf::Texture gameObjectTexture) override;
	};

}