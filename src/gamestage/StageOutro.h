/*
 * StageOutro.h
 *
 *  Created on: 8 Nov 2014
 *      Author: lucas
 */

#ifndef SRC_GAMESTAGE_STAGEOUTRO_H_
#define SRC_GAMESTAGE_STAGEOUTRO_H_

#include "GameStage.h"

class StageOutro: public GameStage
{
	public:
		StageOutro();
		virtual ~StageOutro();

		void init();
		void close();
		void update();

		GAME_STAGE::GAME_STAGE getGameStageEnum();

		void performKeyboardInput(unsigned char key, int x, int y);
		void performSpecialKeyboardInput(int key, int x, int y);
		void performMouseDragg(int x, int y);
		void performMouseAction(int button, int state, int x, int y);
		void reshape(int width, int height);
		void performMouseMove(int x, int y);
		void drawAll();
};

#endif /* SRC_GAMESTAGE_STAGEOUTRO_H_ */
