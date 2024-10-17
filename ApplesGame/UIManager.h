#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Math.h"
#include "Resources.h"

namespace ApplesGame
{
	class UIManager
	{
		struct SwitchGameMode
		{
			uint16_t isApplesEndless : 1;
			uint16_t isAccelerationFromApples : 1;
		};

		struct PlayerRecordTable
		{
			sf::Text PlayerRecordTableUI;
			std::string namePlayer;
			int numberPoint = 0;
		};

		int placeNumberPlayer = 0;
		GameResources resources;
		SwitchGameMode GameMode;
		sf::Text scoreUI, gameOverUI, hintGameOverUI, hintUI, TableRecordUI, ExitDialogUI;

		//Player record TablePlayerRecords data
		PlayerRecordTable TablePlayerRecords[MAX_NUM_PLAYER_RECORD_TABLE];


		//Text GameModeSelect
		sf::Text endlessApplesUI, accelerationUI;
		std::string NamePLayerTableRecord[10] = { "Jon", "King", "Spider", "Doom", "Lucky", "SoJo", "Rick", "James", "45667", "Dark Apple" };

		bool isKeyPressed = false;
		
		void InitializingTextScreen(sf::Text &textScreen, std::string stringScreen, int textSize, sf::Color textColor,
			sf::Font& font, Vector2D gameTextPosition, Vector2D textRevelationOrigin, bool isTextBold = false, bool isVisible = true);
		
		//Functions for sorting the table
		void Swap(int x, int y);
		int Splitting(int low, int high);
		void QuickSortTable(int low, int high);

		void InitializationPlayersInTable();

		void UpdateTextScreen(sf::Text &textScreen, std::string textString);

		void UpdateTextScreen(sf::Text &textScreen, Vector2D gameTextPosition);

	public:

		enum GameState
		{
			Gameplay = 0,
			GameOver,
			GameModes,
			ExitDialog,
			TableRecord
		};

		struct Menu
		{
			GameState gameState = GameState::GameModes;
			Menu* prevGameMenu = nullptr;
		};

		Menu* gameMainMenu = nullptr;

		UIManager()
		{
			InitializationUIManager();
		}

		enum GameModeSelection
		{
			OffMode = 0,
			Acceleration = 1,
			EndlessApples = 2
		};

		void GameStatePush(Menu* gameMenu);
		void GameStatePop();
		Menu* GetGameStateMenu();
		void SortTablePlayerRecords();
		void UpdateNumberScorePlayerInTable(int numberScore);
		void InitializationUIManager();
		const uint16_t GetGameModeMap();
		void DrawTextScreen(sf::RenderWindow& window);
		void SelectGameMode(sf::RenderWindow& window, sf::Event& event);
		void UpdateNumberScore(int numberScore);
	};


}

