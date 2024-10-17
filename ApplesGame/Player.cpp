#include "Player.h"
#include "Game.h"

namespace ApplesGame
{
	void Player::Spawn(Position2D GameObjectPosition)
	{
		position = GameObjectPosition;
		sprite.setTexture(texture);
		SetSpriteSize(sprite, size, size);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		sprite.setPosition({ position.x, position.y });
	}


	void Player::AccelerationPlayer(float acceleration)
	{
		speed += acceleration;
	}

	void Player::ResetAccelerationPlayer()
	{
		speed = INITIAL_SPEED;
	}

	bool Player::CollisionObject(GameObject& contactObject)
	{
		return IsCirclesCollide(position, size,
			contactObject.position, contactObject.size);
	}

	// Initialization and spawn sprite shape object in game 
	void Player::Initialization(float sizeGameObject, Position2D positionGameObject, sf::Texture gameObjectTexture)
	{
		speed = INITIAL_SPEED;
		direction = PlayerDirection::Right;
		position = positionGameObject;
		size = sizeGameObject;
		texture = gameObjectTexture;
		Spawn(position);

	}

	void Player::UpdatePlayerDirection(float& deltaTime)
	{

			// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direction = PlayerDirection::Right;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			direction = PlayerDirection::Left;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			direction = PlayerDirection::Up;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			direction = PlayerDirection::Down;
		}
			
			// Switch player state 
			switch (direction)
			{
			case PlayerDirection::Right:
				position.x += speed * deltaTime;
				break;
			case PlayerDirection::Left:
				position.x -= speed * deltaTime;
				break;
			case PlayerDirection::Up:
				position.y -= speed * deltaTime;
				break;
			case PlayerDirection::Down:
				position.y += speed * deltaTime;
				break;
			default:
				break;
			}

	}

	void Player::Draw(sf::RenderWindow& window)
	{
		
			sprite.setPosition({ position.x, position.y });
			switch (direction)
			{
			case PlayerDirection::Up:
			{
				SetSpriteSize(sprite, size, size);
				sprite.setRotation(-90.f);
				break;
			}
			case PlayerDirection::Right:
			{
				SetSpriteSize(sprite, size, size);
				sprite.setRotation(0.f);
				break;
			}
			case PlayerDirection::Down:
			{
				SetSpriteSize(sprite, size, size);
				sprite.setRotation(90.f);
				break;
			}
			case PlayerDirection::Left:
			{
				SetSpriteSize(sprite, -size, size);
				sprite.setRotation(0.f);
				break;
			}	
			}
			window.draw(sprite);
	}
	


}



