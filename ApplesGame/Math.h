#pragma once
namespace sf 
{
	class Sprite;
	class Text;
}

namespace ApplesGame
{
	struct Vector2D
	{
		float x = 0, y = 0;
	};

	typedef Vector2D Position2D;

	Position2D GetRandomPotisionInScreen(float screenWidth, float screenHeight);

	int GetRandomCountObjectScreen(int min_number, int max_number);

	bool IsCirclesCollide(Position2D rect1Position, float circle1Radius, Position2D rect2Position, float circle2Radius);

	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Position2D rect2Size);

	void SetSpriteSize(sf::Sprite& sprite, float desireWidth, float desiredHeight);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);

	void SetTextRelativeOrigin(sf::Text& text, const Position2D& relativePosition);
}



