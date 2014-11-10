#include "StageDeathCause.h"

#include <GL/freeglut.h>

#include "../Camera.h"
#include "../gui/StringDrawer.h"
#include "../Colors.h"
#include "GameStateManager.h"


StageDeathCause::StageDeathCause()
{
	flickeringColor = new FlickeringColor(1000, Colors::DarkBlue);
}

StageDeathCause::~StageDeathCause()
{
	delete flickeringColor;
}

void StageDeathCause::init()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	deathCause = GameStateManager::getProperty(Properties::DEATH_CAUSE);
	points = "Your result is " + GameStateManager::getProperty(Properties::NEW_HIGHSCORE_VALUE);
}

void StageDeathCause::close()
{

}

void StageDeathCause::update()
{
	flickeringColor->update();
	drawAll();
}

GAME_STAGE::GAME_STAGE StageDeathCause::getGameStageEnum()
{
	return GAME_STAGE::DEATH_SCREEN;
}

void StageDeathCause::performKeyboardInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 32:
			GameStateManager::startMenuState();
			break;
		default:
			break;
	}
}

void StageDeathCause::performSpecialKeyboardInput(int key, int x, int y)
{

}

void StageDeathCause::performMouseDragg(int x, int y)
{

}

void StageDeathCause::performMouseAction(int button, int state, int x, int y)
{

}

void StageDeathCause::reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble) height;

	gluPerspective(90, aspect, 1.0, 5.0);
}

void StageDeathCause::performMouseMove(int x, int y)
{

}

void StageDeathCause::drawAll()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera::setStaticVision();

	StringDrawer::drawString("You are dead because", -0.9, .5f, 0 , GLUT_BITMAP_9_BY_15);

	StringDrawer::drawString(deathCause, -0.045 * deathCause.size(), -0, 0, GLUT_BITMAP_TIMES_ROMAN_24, Colors::Red);

	StringDrawer::drawString(points, -0.045 * points.size(), -.5f, 0, GLUT_BITMAP_9_BY_15);

	StringDrawer::drawString("press SPACE to continue...", -0.5, -2.6f, 0, GLUT_BITMAP_HELVETICA_10, flickeringColor->getColor());

	glFlush();

	glutSwapBuffers();
}
