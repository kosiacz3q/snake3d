#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

#include <string>
#include <map>

#include "GameStage.h"
#include "PropertiesEnumerations.hpp"

class GameStateManager
{
	public:
		static void init();
		static void startGameState();
		static void startMenuState();
		static void startIntroState();
		static void startOutroState();
		static void startDeathScreenState();
		static GameStage* getActualGameStage();
		static void close();

		static std::string getProperty(Properties::PropertiesEnum);
		static void setProperty(Properties::PropertiesEnum, std::string value);

	private:
		GameStateManager();
		static std::map<Properties::PropertiesEnum, std::string>* gameGlobalProperties;
		static GameStage* actualState;
};

#endif /* GAMESTATEMANAGER_H_ */
