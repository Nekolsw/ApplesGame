#include "UIManager.h"

namespace ApplesGame
{
	void UIManager::InitializingTextScreen(sf::Text &textScreen, std::string stringScreen, int textSize, sf::Color textColor, sf::Font& font, Vector2D gameTextPosition, Vector2D textRevelationOrigin, bool isTextBold, bool isVisible)
	{
		textScreen.setString(stringScreen);
		textScreen.setCharacterSize(textSize);
		textScreen.setFillColor(textColor);
		textScreen.setFont(font);
		if (isTextBold) 
		{
			textScreen.setStyle(sf::Text::Bold);
		}
		else 
		{
			textScreen.setStyle(sf::Text::Regular);
		}
		SetTextRelativeOrigin(textScreen, textRevelationOrigin);
		textScreen.setPosition({gameTextPosition.x, gameTextPosition.y });
	}

	void UIManager::Swap(int x, int y)
	{
		PlayerRecordTable temp = TablePlayerRecords[x];
		TablePlayerRecords[x] = TablePlayerRecords[y];
		TablePlayerRecords[y] = temp;
		if (TablePlayerRecords[x].namePlayer == "PLAYER") 
		{
			placeNumberPlayer = x;
		}

		else if (TablePlayerRecords[y].namePlayer == "PLAYER") 
		{
			placeNumberPlayer = y;
		}
	}

	int UIManager::Splitting(int low, int high)
	{
		int pivot = TablePlayerRecords[high].numberPoint;
		int x = (low - 1);

		for (int y = low; y <= high - 1; y++) {

			if (TablePlayerRecords[y].numberPoint > pivot) {
				x++;
				Swap(x, y);
			}
		}
		Swap(x + 1, high);
		return (x + 1);
	}

	void UIManager::QuickSortTable(int low, int high)
	{
		if (low < high) {

			int array_partition = Splitting(low, high);

			QuickSortTable(low, array_partition - 1);

			QuickSortTable(array_partition + 1, high);
		}
	}

	void UIManager::GameStatePush(Menu* gameMenu)
	{
		if (gameMainMenu->gameState != gameMenu->gameState)
		{
			Menu* newMenu = new Menu{ gameMenu->gameState,  gameMainMenu };
			gameMainMenu = newMenu;
		}
	}

	void UIManager::GameStatePop()
	{
		if (gameMainMenu->prevGameMenu == nullptr) 
		{
			return;
		}

		Menu* oldMenu = gameMainMenu;
		gameMainMenu = gameMainMenu->prevGameMenu;
		delete oldMenu;
	}

	UIManager::Menu* UIManager::GetGameStateMenu()
	{
		return gameMainMenu;
	}

	void UIManager::SortTablePlayerRecords()
	{
		int size = MAX_NUM_PLAYER_RECORD_TABLE - 1;
		QuickSortTable(0, size);

		for (int i = 0; i < MAX_NUM_PLAYER_RECORD_TABLE; i++)
		{
			UpdateTextScreen(TablePlayerRecords[i].PlayerRecordTableUI, std::to_string(i + 1) + ". " + TablePlayerRecords[i].namePlayer + ": " + std::to_string(TablePlayerRecords[i].numberPoint));
			UpdateTextScreen(TablePlayerRecords[i].PlayerRecordTableUI, Vector2D{ 300.f, 215.f + 40 * i });
		}
	}

	void UIManager::InitializationPlayersInTable()
	{
		placeNumberPlayer = MAX_NUM_PLAYER_RECORD_TABLE - 1;
		int randomNamePlayer = 0;
		for (int i = 0; i < MAX_NUM_PLAYER_RECORD_TABLE - 1; i++) 
		{
			//Ñhecking that the name does not match the names in the table
			for (;;) 
			{
				bool isPlayerNotInTable = true;
				randomNamePlayer = rand() % sizeof(NamePLayerTableRecord) / sizeof(NamePLayerTableRecord[0]);

				for (int j = 0; j < MAX_NUM_PLAYER_RECORD_TABLE - 1; j++)
				{
					if (NamePLayerTableRecord[randomNamePlayer] == TablePlayerRecords[j].namePlayer) { isPlayerNotInTable = false; break; }
				}
				if (isPlayerNotInTable)
				{
					break;
				}
			}

			TablePlayerRecords[i].namePlayer = NamePLayerTableRecord[randomNamePlayer];
			TablePlayerRecords[i].numberPoint = 3 + rand() % 16;
			
			InitializingTextScreen(TablePlayerRecords[i].PlayerRecordTableUI, std::to_string(i + 1) + ". " + TablePlayerRecords[i].namePlayer + ": " + std::to_string(TablePlayerRecords[i].numberPoint),
				35, sf::Color(148, 0, 211), resources.fontText, {300.f, 215.f + 40 * i }, {0.0f, 0.0f});
		}

		InitializingTextScreen(TableRecordUI, "HIGH SCORE", 50, sf::Color::Yellow, resources.fontText, { 400.f, 180.f}, { 0.5f, 0.5f });
		TablePlayerRecords[placeNumberPlayer].namePlayer = "PLAYER";
		TablePlayerRecords[placeNumberPlayer].numberPoint = 0;
		InitializingTextScreen(TablePlayerRecords[placeNumberPlayer].PlayerRecordTableUI, std::to_string(placeNumberPlayer + 1) + ". " + TablePlayerRecords[placeNumberPlayer].namePlayer + ": " + std::to_string(TablePlayerRecords[placeNumberPlayer].numberPoint),
			35, sf::Color(148, 0, 211), resources.fontText, { 300.f, 215.f + 40 * placeNumberPlayer }, { 0.0f, 0.0f });
	}

	void UIManager::UpdateNumberScorePlayerInTable(int numberScore)
	{
		if (TablePlayerRecords[placeNumberPlayer].numberPoint < numberScore) 
		{
			TablePlayerRecords[placeNumberPlayer].numberPoint = numberScore;
		}
	}

	void UIManager::InitializationUIManager()
	{
		InitializingResources(resources);
		GameMode.isApplesEndless = 0;
		GameMode.isAccelerationFromApples = 0;
		gameMainMenu = new Menu{ GameState::GameModes, nullptr };
		InitializingTextScreen(scoreUI, "Score: " + std::to_string(0), 18, sf::Color::Yellow, resources.fontText, { 40.f, 11.f }, { 0.5f, 0.5f });
		InitializingTextScreen(ExitDialogUI, "Exit to Menu? \nY - Yes\nN - No", 24, sf::Color(148, 0, 211), resources.fontText, { 400.f, 300.f }, { 0.5f, 0.5f });
		InitializingTextScreen(gameOverUI, "GameOver", 60, sf::Color(148, 0, 211), resources.fontText, { 400.f, 300.f }, { 0.5f, 0.5f }, false, false);
		InitializingTextScreen(hintGameOverUI, "Space to restart", 22, sf::Color::White, resources.fontText, { 400.f, 350.f }, { 0.5f, 0.5f }, false, false);
		InitializingTextScreen(hintUI, "WASD or arrows to move, ESC exit to menu\nL - Table of records", 18, sf::Color::White, resources.fontText, { 610.f, 20.f }, { 0.5f, 0.5f }, false, true);
		InitializingTextScreen(endlessApplesUI, "1.Mode: Endeless Apples", 22, sf::Color::White, resources.fontText, { 290.f, 275.f }, { 0.f, 0.f }, false, true);
		InitializingTextScreen(accelerationUI, "2.Acceleration from apples", 22, sf::Color::White, resources.fontText, { 290.f, 300.f }, { 0.f, 0.f }, false, true);
		InitializationPlayersInTable();
	}

	void UIManager::UpdateTextScreen(sf::Text &textScreen, std::string text)
	{
		textScreen.setString(text);
	}

	void UIManager::UpdateTextScreen(sf::Text& textScreen, Vector2D gameTextPosition)
	{
		textScreen.setPosition({ gameTextPosition.x, gameTextPosition.y });
	}

	const uint16_t UIManager::GetGameModeMap()
	{
		return (GameMode.isApplesEndless << 1 | GameMode.isAccelerationFromApples);
	}

	void UIManager::DrawTextScreen(sf::RenderWindow& window)
	{
			window.draw(scoreUI);
			window.draw(hintUI);

		switch (gameMainMenu->gameState)
		{
		case GameState::GameModes:
			window.draw(endlessApplesUI);
			window.draw(accelerationUI);
			break;
		case GameState::GameOver:
			window.draw(gameOverUI);
			window.draw(hintGameOverUI);
			break;
			
		case GameState::ExitDialog:
			window.draw(ExitDialogUI);
			break;
		case GameState::TableRecord:
			window.draw(TableRecordUI);
			for (int i = 0; i < MAX_NUM_PLAYER_RECORD_TABLE - 1; i++)
			{
				window.draw(TablePlayerRecords[i].PlayerRecordTableUI);
			}
			break;
		default:
			break;
		}
	}


	// Writing to a bitmap(1 bit) GameMode
	void UIManager::SelectGameMode(sf::RenderWindow& window, sf::Event& event)
	{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !isKeyPressed)
			{
				GameMode.isApplesEndless = ~GameMode.isApplesEndless;
				if (GameMode.isApplesEndless)
				{
					InitializingTextScreen(endlessApplesUI, "1.Mode: Endeless Apples", 22, sf::Color(148, 0, 211), resources.fontText, { 290.f, 275.f }, { 0.f, 0.f }, false, true);
				}
				else
				{
					InitializingTextScreen(endlessApplesUI, "1.Mode: Endeless Apples", 22, sf::Color::White, resources.fontText, { 290.f, 275.f }, { 0.f, 0.f }, false, true);
				}

				isKeyPressed = true;
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !isKeyPressed)
			{

				GameMode.isAccelerationFromApples = ~GameMode.isAccelerationFromApples;
				if (GameMode.isAccelerationFromApples)
				{
					InitializingTextScreen(accelerationUI, "2.Acceleration from apples", 22, sf::Color(148, 0, 211), resources.fontText, { 290.f, 300.f }, { 0.f, 0.f }, false, true);
				}
				else
				{
					InitializingTextScreen(accelerationUI, "2.Acceleration from apples", 22, sf::Color::White, resources.fontText, { 290.f, 300.f }, { 0.f, 0.f }, false, true);
				}

				isKeyPressed = true;

			}
			else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)))
			{
				if (isKeyPressed)
				{
					isKeyPressed = false;
				}
			}
		
	}

	void UIManager::UpdateNumberScore(int numberScore)
	{
		UpdateTextScreen(scoreUI, "Score: " + std::to_string(numberScore));
	}

}