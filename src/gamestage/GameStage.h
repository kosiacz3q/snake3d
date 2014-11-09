#ifndef SRC_GAMESTAGE_GAMESTAGE_H_
#define SRC_GAMESTAGE_GAMESTAGE_H_

#include "GameStageEnum.hpp"

class GameStage
{
	public:
		GameStage();
		virtual ~GameStage();

		virtual GAME_STAGE::GAME_STAGE getGameStageEnum() = 0;

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void close() = 0;

		virtual void performKeyboardInput(unsigned char key, int x, int y) = 0;
		virtual void performSpecialKeyboardInput(int key, int x, int y) = 0;
		virtual void performMouseDragg(int x, int y) = 0;
		virtual void performMouseAction(int button, int state, int x, int y) = 0;
		virtual void reshape(int width, int height) = 0;
		virtual void performMouseMove(int x, int y) = 0;
};

#endif /* SRC_GAMESTAGE_GAMESTAGE_H_ */
