#include "GameStateManager.h"
#include "GameStageStaticWrapper.h"

#include "StageGame.h"
#include "StageMenu.h"
#include "StageIntro.h"
#include "StageOutro.h"
#include "StageDeathCause.h"

GameStage* GameStateManager::actualState = nullptr;
std::map<Properties::PropertiesEnum, std::string>* GameStateManager::gameGlobalProperties = nullptr;

GameStateManager::GameStateManager()
{

}

void GameStateManager::startGameState()
{
	GameStage* newState = new StageGame();
	GameStageStaticWrapper::changeGameStage(newState);
	delete GameStateManager::actualState;
	GameStateManager::actualState = newState;

}

void GameStateManager::startMenuState()
{
	GameStage* newState = new StageMenu();
	GameStageStaticWrapper::changeGameStage(newState);
	delete GameStateManager::actualState;
	GameStateManager::actualState = newState;
}

void GameStateManager::startIntroState()
{
	GameStage* newState = new StageIntro();
	GameStageStaticWrapper::changeGameStage(newState);
	delete GameStateManager::actualState;
	GameStateManager::actualState = newState;
}

void GameStateManager::startOutroState()
{
	GameStage* newState = new StageOutro();
	GameStageStaticWrapper::changeGameStage(newState);
	delete GameStateManager::actualState;
	GameStateManager::actualState = newState;
}

void GameStateManager::startDeathScreenState()
{
	GameStage* newState = new StageDeathCause();
	GameStageStaticWrapper::changeGameStage(newState);
	delete GameStateManager::actualState;
	GameStateManager::actualState = newState;
}

void GameStateManager::close()
{
	GameStageStaticWrapper:close();
	delete actualState;
	delete gameGlobalProperties;
}

GameStage* GameStateManager::getActualGameStage()
{
	return GameStageStaticWrapper::getGameStage();
}

void GameStateManager::init()
{
	GameStageStaticWrapper::init();

	gameGlobalProperties = new std::map<Properties::PropertiesEnum, std::string>();
}

std::string GameStateManager::getProperty(Properties::PropertiesEnum name)
{
	auto iter = gameGlobalProperties->find(name);

	if (iter != gameGlobalProperties->end())
		return iter->second;
	else
		return "";
}

void GameStateManager::setProperty(Properties::PropertiesEnum name, std::string value)
{
	gameGlobalProperties->erase(name);

	gameGlobalProperties->insert(std::pair<Properties::PropertiesEnum,std::string>(name,value));
}

