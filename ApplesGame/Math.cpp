#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Math.h"


namespace ApplesGame
{
	Position2D GetRandomPotisionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	int GetRandomCountObjectScreen(int min_number, int max_number)
	{
		return rand() % (max_number + 1 - min_number) + min_number;
	};

	bool IsCirclesCollide(Position2D rect1Position, float circle1Radius,
		Position2D rect2Position, float circle2Radius)
	{
		float squareDistance = (rect1Position.x - rect2Position.x) * (rect1Position.x - rect2Position.x) + (rect1Position.y - rect2Position.y) * (rect1Position.y - rect2Position.y);
		float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius) / 4;
		return squareDistance <= squareRadiusSum;
	}

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size,
		Position2D rect2Position, Position2D rect2Size)
	{
		if ((rect1Position.x - rect2Position.x) + (rect1Position.y - rect2Position.y) < (rect1Size.x + rect2Size.x) + (rect1Size.y + rect2Size.y)) //Preliminary range check 
		{
		float dx = (float)fabs(rect1Position.x - rect2Position.x);
		float dy = (float)fabs(rect1Position.y - rect2Position.y);

		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
			dy <= (rect1Size.y + rect2Size.y) / 2.f);
		}
		else
		{
			return false;
		}

	}
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

	void SetTextRelativeOrigin(sf::Text& text, const Position2D& relativePosition)
	{
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin((textRect.left + textRect.width) * relativePosition.x, (textRect.top + textRect.height) * relativePosition.y);
	}
}


