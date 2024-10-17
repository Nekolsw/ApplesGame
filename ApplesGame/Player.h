#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"
#include "GameObject.h"

namespace ApplesGame
{
	class Player : public GameObject {
	protected:
		float speed = INITIAL_SPEED;

	public:
		enum class PlayerDirection
		{
			Right = 0,
			Left,
			Up,
			Down
		};
		PlayerDirection direction = PlayerDirection::Right;

		void Spawn(Position2D GameObjectPosition) override;
		bool CollisionObject(GameObject& contactObject);
		void AccelerationPlayer(float acceleration);
		void ResetAccelerationPlayer();
		void Initialization(float sizeGameObject, Position2D positionGameObject, sf::Texture gameObjectTexture) override;
		void Draw(sf::RenderWindow& window) override;
		void UpdatePlayerDirection(float& deltaTime);





	};
	
}


