#pragma once
#include "GameObject.h"
#include "Math.h"
namespace ApplesGame
{
	class PickupItem : public GameObject
	{
	protected:
		bool isItemPicked = false;
	public:
		void Spawn(Position2D GameObjectPosition) override;
		void Delete();
		bool GetIsItemPicked();
	};
}