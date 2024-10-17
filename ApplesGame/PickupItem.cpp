#include "PickupItem.h"
#include "Constants.h"

namespace ApplesGame 
{
	void PickupItem::Spawn(Position2D GameObjectPosition)
	{
		isItemPicked = false;
		position = GameObjectPosition;
		sprite.setTexture(texture);
		SetSpriteSize(sprite, size, size);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		sprite.setPosition({ position.x, position.y });
	}

	void PickupItem::Delete()
	{
		isItemPicked = true;
		position = { SCREEN_WIDTH + size, SCREEN_HEIGHT + size }; // !!!CRUTCH, removing an object from field.
	}

	bool PickupItem::GetIsItemPicked()
	{
		return isItemPicked;
	}

	



}