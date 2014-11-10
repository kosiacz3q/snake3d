/*
 * StageOutro.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: lucas
 */

#include "StageOutro.h"

#include <GL/freeglut.h>

StageOutro::StageOutro()
{


}

StageOutro::~StageOutro()
{

}

void StageOutro::init()
{
	glutSetCursor(GLUT_CURSOR_NONE);
}

void StageOutro::close()
{

}

void StageOutro::update()
{

}

GAME_STAGE::GAME_STAGE StageOutro::getGameStageEnum()
{
	return GAME_STAGE::OUTRO;
}

void StageOutro::performKeyboardInput(unsigned char key, int x, int y)
{

}

void StageOutro::performSpecialKeyboardInput(int key, int x, int y)
{

}

void StageOutro::performMouseDragg(int x, int y)
{

}

void StageOutro::performMouseAction(int button, int state, int x, int y)
{

}

void StageOutro::reshape(int width, int height)\
{

}

void StageOutro::performMouseMove(int x, int y)
{

}

void StageOutro::drawAll()
{

}

