// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"
#include "UIManager.h"
#include "Game.h"

int main()
{
	using namespace ApplesGame;
	int seed = (int)time(nullptr);
	srand(seed);

	// Initialized window 
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples game");
	window.setKeyRepeatEnabled(false);
	//Game initialized
	Game game;
	game.RunApplication(game.gameStruct);

	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	
	// Main loop
	while (window.isOpen())
	{
		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		

		// Read events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				break;
			}


			// Update game state
			if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && game.GetUIManager().GetGameStateMenu()->gameState == game.GetUIManager().GameState::GameOver)
			{
				while (game.GetUIManager().GetGameStateMenu()->prevGameMenu != nullptr)
				{
					game.GetUIManager().GameStatePop();
				}
			}

			else if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && game.GetUIManager().GetGameStateMenu()->gameState != game.GetUIManager().GameState::ExitDialog)
			{
				game.GetUIManager().GameStatePop();
			}

			if (sf::Event::KeyPressed && game.GetUIManager().GetGameStateMenu()->gameState == game.GetUIManager().GameState::ExitDialog)
			{
				
				if (event.key.code == sf::Keyboard::Y)
				{
					game.GetUIManager().GameStatePop();
				}
				else if (event.key.code == sf::Keyboard::N)
				{

					game.MainMenu.gameState = game.GetUIManager().GameState::Gameplay;
					game.GetUIManager().GameStatePush(&game.MainMenu);
				}
			}

			if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && game.GetUIManager().GetGameStateMenu()->gameState == game.GetUIManager().GameState::GameModes)
			{
				game.MainMenu.gameState = game.GetUIManager().GameState::ExitDialog;
				game.GetUIManager().GameStatePush(&game.MainMenu);
				game.MainMenu.gameState = game.GetUIManager().GameState::Gameplay;
				game.GetUIManager().GameStatePush(&game.MainMenu);

				game.gameStruct.modeMap = game.GetUIManager().GetGameModeMap();
				game.RestartGame(game.gameStruct);
			}

			else if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && game.GetUIManager().GetGameStateMenu()->gameState == game.GetUIManager().GameState::GameOver)
			{
				game.GetUIManager().GameStatePop();

				game.gameStruct.modeMap = game.GetUIManager().GetGameModeMap();
				game.RestartGame(game.gameStruct);
			}

			if (sf::Event::KeyPressed && event.key.code == sf::Keyboard::L && game.GetUIManager().GetGameStateMenu()->gameState == game.GetUIManager().GameState::GameModes)
			{
				game.MainMenu.gameState = game.GetUIManager().GameState::TableRecord;
				game.GetUIManager().GameStatePush(&game.MainMenu);
				game.GetUIManager().SortTablePlayerRecords();
			}

		}

		
		game.UpdateGame(game.gameStruct, deltaTime, window, event);


		// Draw game
		window.clear();
		game.DrawGame(game.gameStruct, window);
		window.display();
	}

	//Deinitialization
	game.DeinializeGame(game.gameStruct);

	return 0;
}
