#include <cassert>
#include "Game.h"

namespace ApplesGame
{

	UIManager& Game::GetUIManager()
	{
		static UIManager uiManager = UIManager();
		return uiManager;
		
	}

	void Game::Playback(sf::SoundBuffer& buffer)
	{
		gameStruct.soundGame.setBuffer(buffer);
		gameStruct.soundGame.play();
	}

	void Game::GameOver(GameStruct& gameStruct)
	{
		Playback(gameStruct.resources.playerDeath);
		GetUIManager().UpdateNumberScorePlayerInTable(gameStruct.numEatenApples);
		MainMenu.gameState = GetUIManager().GameState::GameOver;
		GetUIManager().GameStatePush(&MainMenu);
	}

	void Game::RunApplication(GameStruct& gameStruct)
	{
		InitializingResources(gameStruct.resources);
		gameStruct.modeMap = 0;
		gameStruct.player.Initialization(PLAYER_SIZE, { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f }, gameStruct.resources.playerTexture);
		GetUIManager();
		gameStruct.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		gameStruct.background.setFillColor(sf::Color(31, 31, 31));
		gameStruct.background.setPosition(0.f, 0.f);
	}

	void Game::RestartGame(GameStruct& gameStruct)
	{

		gameStruct.apples.clear();
		gameStruct.rocks.clear();

		//Reset background
		gameStruct.background.setFillColor(sf::Color::Black);

		gameStruct.numEatenApples = 0;

		//Reset speed player
		gameStruct.player.ResetAccelerationPlayer();

		//game.timeSinceGameFinish = 0;

		//Initialization player and spawn
		gameStruct.player.Spawn({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f});

		//Initialization and spawn apple
		int numApple = GetRandomCountObjectScreen(MIN_NUM_APPLES, MAX_NUM_APPLES);
		gameStruct.apples.resize(numApple);
		gameStruct.rocks.resize(NUM_ROCKS);

		
		//Initialization apples
		for (Apple& apples : gameStruct.apples)
		{
			apples.Initialization(APPLE_SIZE, GetRandomPotisionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT), gameStruct.resources.appleTexture);
		}

		//Initialization rocks
		for (Rock& rocks : gameStruct.rocks)
		{
			rocks.Initialization(ROCK_SIZE, GetRandomPotisionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT), gameStruct.resources.rockTexture);
		}

		//Spawn apples (Random num)
		for (Apple& apples : gameStruct.apples)
		{
			apples.Spawn(GetRandomPotisionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
		
		}

		//Initialization and spawn rocks
		for (Rock& rocks : gameStruct.rocks)
		{
			rocks.Spawn(GetRandomPotisionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT));
		}

		GetUIManager().UpdateNumberScorePlayerInTable(gameStruct.numEatenApples);
	}

	void Game::UpdateGame(GameStruct& gameStruct, float deltaTime, sf::RenderWindow& window, sf::Event& event)
	{
		if (GetUIManager().GetGameStateMenu()->gameState == GetUIManager().GameState::Gameplay)
		{
			if (GetUIManager().GetGameStateMenu()->gameState != GetUIManager().GameState::ExitDialog)
			{
				gameStruct.player.UpdatePlayerDirection(deltaTime);
			}

			GetUIManager().UpdateNumberScore(gameStruct.numEatenApples);
			//Check collision with a apples
			for (Apple& apples : gameStruct.apples)
			{
				if (gameStruct.player.CollisionObject(apples))
				{
					gameStruct.numEatenApples++;
					Playback(gameStruct.resources.appleEat);
					
					if (gameStruct.modeMap & GetUIManager().Acceleration)
					{
						gameStruct.player.AccelerationPlayer(apples.GetAcceleration());
					}
					if (gameStruct.modeMap & GetUIManager().EndlessApples)
					{
						apples.Spawn(GetRandomPotisionInScreen(SCREEN_WIDTH - APPLE_SIZE, SCREEN_HEIGHT - APPLE_SIZE));
					}
					else 
					{
						apples.Delete();
						if (gameStruct.numEatenApples == gameStruct.apples.size())
						{ 
							RestartGame(gameStruct);
						}
					}
				}


			}
			//Check collision with a stones
			for (Rock& rocks : gameStruct.rocks)
			{
				if (gameStruct.player.CollisionObject(rocks))
				{
					GameOver(gameStruct);
				}

			}

			//Check screen border collision 
			if (gameStruct.player.position.x < 0.f + PLAYER_SIZE / 2.f || gameStruct.player.position.x > SCREEN_WIDTH - PLAYER_SIZE / 2.f ||
				gameStruct.player.position.y < 0.f + PLAYER_SIZE / 2.f || gameStruct.player.position.y > SCREEN_HEIGHT - PLAYER_SIZE / 2.f)
			{
				GameOver(gameStruct);
			}

		}

		if (GetUIManager().GetGameStateMenu()->gameState == GetUIManager().GameState::GameModes)
		{
			// Ñhanging the background during a pause
			/*if (game.timeSinceGameFinish <= PAUSE_LENGHT)
			{
				game.timeSinceGameFinish += deltaTime;
				game.background.setFillColor(sf::Color(31, 31, 31));
				game.isGamePause = true;
			}*/

			GetUIManager().SelectGameMode(window, event);
		}
	}

	void Game::DrawGame(GameStruct& gameStruct, sf::RenderWindow& window)
	{
		window.draw(gameStruct.background);
		if (GetUIManager().GetGameStateMenu()->gameState == GetUIManager().GameState::Gameplay || GetUIManager().GetGameStateMenu()->gameState == GetUIManager().GameState::ExitDialog)
		{
			gameStruct.player.Draw(window);

			for (Rock rocks : gameStruct.rocks)
			{
				rocks.Draw(window);
			}

			for (Apple apples : gameStruct.apples)
			{
				apples.Draw(window);
			}
		}
		GetUIManager().DrawTextScreen(window);
	}

	void Game::DeinializeGame(GameStruct& gameStruct)
	{

	}
}

