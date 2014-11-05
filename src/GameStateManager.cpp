#include "GameStateManager.h"

int GameStateManager::actualState = 0;

GameStateManager::GameStateManager()
{

}

void GameStateManager::startGameState()
{
	GameStateManager::clean();
	GameStateManager::actualState = GAME_STATE::GAME;
	Game::init();
}

void GameStateManager::startMenuState()
{
	GameStateManager::clean();
	GameStateManager::actualState = GAME_STATE::MENU;
	Menu::init();
}

void GameStateManager::clean()
{
	switch (actualState)
	{
		case GAME_STATE::GAME:
			Game::close();
			break;
		case GAME_STATE::MENU:
			Menu::close();
			break;
		default:
			break;
	}
}

void GameStateManager::close()
{
	GameStateManager::clean();
}
