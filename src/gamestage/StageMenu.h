#ifndef MENU_H_
#define MENU_H_

#include <vector>

#include "../gui/TextInFrame.h"
#include "../highscore/HighscoreHandler.h"
#include "GameStage.h"


class StageMenu : public GameStage
{
	public:
		StageMenu();
		virtual ~StageMenu();

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
		void initHighScores();
		HighscoreHandler* highscoreHandler;
		std::vector<TextInFrame> highscores;
};

#endif /* MENU_H_ */
