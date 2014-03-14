/*
 * GameStateManager.h
 *
 *  Created on: Sep 27, 2013
 *      Author: lucas
 */

#ifndef GAMESTATEMANAGER_H_
#define GAMESTATEMANAGER_H_

//#define DEBUG 1

#include "Game.h"
#include "Menu.h"

namespace GAME_STATE{
	enum {
		GAME = 1,
		MENU = 2
	};
}

class GameStateManager {
public:
	static void startGameState();
	static void startMenuState();
	static int actualState;
	static void close();
private:
	GameStateManager();
	static void clean();
};

#endif /* GAMESTATEMANAGER_H_ */
