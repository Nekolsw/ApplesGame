#pragma once
#include "GameObject.h"
namespace ApplesGame
{						 
	class Obstacle : public GameObject
	{
	public:
		void Spawn(Position2D GameObjectPosition) override;
	};

}