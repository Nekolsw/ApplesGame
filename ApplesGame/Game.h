#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "PickupItem.h"
#include "Apple.h"
#include "Rock.h"
#include "Resources.h"
#include "UIManager.h"

namespace ApplesGame
{
	
	class Game {

		struct GameStruct
		{
			sf::Sound soundGame;
			uint16_t modeMap : 2;
			GameResources resources;
			Player player;
			std::vector<Rock> rocks;
			std::vector<Apple> apples;
			//Global Game data
			int numEatenApples = 0;
			int numApple = 0;
			//float timeSinceGameFinish = 0.f;
			sf::RectangleShape background;
		};

	public:

		GameStruct gameStruct;
		
		UIManager::Menu MainMenu;

		UIManager &GetUIManager();

		void Playback(sf::SoundBuffer& buffer);

		void GameOver(GameStruct& gameStruct);

		void RunApplication(GameStruct& gameStruct);

		void RestartGame(GameStruct& gameStruct);

		void UpdateGame(GameStruct& gameStruct, float deltaTime, sf::RenderWindow& window, sf::Event& event);

		void DrawGame(GameStruct& gameStruct, sf::RenderWindow& window);

		void DeinializeGame(GameStruct& gameStruct);

	};
}


