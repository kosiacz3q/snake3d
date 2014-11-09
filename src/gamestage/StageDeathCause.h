#ifndef SRC_GAMESTAGE_STAGEDEATHCAUSE_H_
#define SRC_GAMESTAGE_STAGEDEATHCAUSE_H_

#include "GameStage.h"

#include "../gui/FlickeringColor.h"


class StageDeathCause: public GameStage
{
	public:
		StageDeathCause();
		virtual ~StageDeathCause();

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

	private:
		FlickeringColor* flickeringColor;
		std::string deathCause;
		std::string points;
};

#endif /* SRC_GAMESTAGE_STAGEDEATHCAUSE_H_ */
