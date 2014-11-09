#ifndef SRC_GAMESTAGE_GAMESTAGESTATICWRAPPER_H_
#define SRC_GAMESTAGE_GAMESTAGESTATICWRAPPER_H_

#include "GameStage.h"


class GameStageStaticWrapper
{
	public:
		static void init();
		static void update();
		static void close();
		static void changeGameStage(GameStage* gm);

		static void performKeyboardInput(unsigned char key, int x, int y);
		static void performSpecialKeyboardInput(int key, int x, int y);
		static void performMouseDragg(int x, int y);
		static void performMouseAction(int button, int state, int x, int y);
		static void reshape(int width, int height);
		static void performMouseMove(int x, int y);

		static GameStage* getGameStage();

	private:
		~GameStageStaticWrapper();
		GameStageStaticWrapper()
		{
		}
		;
		static GameStage* stageHandler;
};

#endif /* SRC_GAMESTAGE_GAMESTAGESTATICWRAPPER_H_ */
