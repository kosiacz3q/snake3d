#include "GameStageStaticWrapper.h"
#include <boost/lexical_cast.hpp>
#include <GL/freeglut.h>

GameStage* GameStageStaticWrapper::stageHandler = nullptr;

void GameStageStaticWrapper::init()
{
	glutReshapeFunc(GameStageStaticWrapper::reshape);
	glutKeyboardFunc(GameStageStaticWrapper::performKeyboardInput);
	glutSpecialFunc(GameStageStaticWrapper::performSpecialKeyboardInput);
	glutMouseFunc(GameStageStaticWrapper::performMouseAction);
	glutMotionFunc(GameStageStaticWrapper::performMouseDragg);
	glutPassiveMotionFunc(GameStageStaticWrapper::performMouseMove);
	glutIdleFunc(GameStageStaticWrapper::update);
}

void GameStageStaticWrapper::update()
{
	GameStageStaticWrapper::stageHandler->update();
}

void GameStageStaticWrapper::performKeyboardInput(unsigned char key, int x, int y)
{
	GameStageStaticWrapper::stageHandler->performKeyboardInput(key, x, y);
}

void GameStageStaticWrapper::performSpecialKeyboardInput(int key, int x, int y)
{
	GameStageStaticWrapper::stageHandler->performSpecialKeyboardInput(key, x, y);
}

void GameStageStaticWrapper::performMouseDragg(int x, int y)
{
	GameStageStaticWrapper::stageHandler->performMouseDragg(x, y);
}

void GameStageStaticWrapper::performMouseAction(int button, int state, int x, int y)
{
	GameStageStaticWrapper::stageHandler->performMouseAction(button, state, x, y);
}

void GameStageStaticWrapper::reshape(int width, int height)
{
	GameStageStaticWrapper::stageHandler->reshape(width, height);
}

void GameStageStaticWrapper::performMouseMove(int x, int y)
{
	GameStageStaticWrapper::stageHandler->performMouseMove(x, y);
}

void GameStageStaticWrapper::close()
{
	if(stageHandler != nullptr)
	{
		GameStageStaticWrapper::stageHandler->close();
		stageHandler = nullptr;
	}
}

void GameStageStaticWrapper::changeGameStage(GameStage* gm)
{
	close();
	stageHandler = gm;
	gm->init();
}

GameStage* GameStageStaticWrapper::getGameStage()
{
	return stageHandler;
}
