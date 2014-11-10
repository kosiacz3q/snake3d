#include "StageIntro.h"

#include <GL/freeglut.h>

#include "GameStateManager.h"
#include "../gui/StringDrawer.h"
#include "../Camera.h"
#include "../Colors.h"

StageIntro::StageIntro()
{
	flickeringColor = new FlickeringColor(2000, Colors::DarkBlue);
	logo = new Texture();
}

StageIntro::~StageIntro()
{
	delete flickeringColor;
	delete logo;
}

void StageIntro::init()
{
	glutSetCursor(GLUT_CURSOR_NONE);

	Camera::reset();
	Camera::setPosition(Vector3f(0., 0., 3.));

	logo->loadTextureFromFile("tex/logo.png");
}

void StageIntro::close()
{
	logo->freeTexture();
}

void StageIntro::update()
{
	flickeringColor->update();
	drawAll();
}

GAME_STAGE::GAME_STAGE StageIntro::getGameStageEnum()
{
	return GAME_STAGE::INTRO;
}

void StageIntro::performKeyboardInput(unsigned char key, int x, int y)
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

void StageIntro::performSpecialKeyboardInput(int key, int x, int y)
{

}

void StageIntro::performMouseDragg(int x, int y)
{

}

void StageIntro::performMouseAction(int button, int state, int x, int y)
{

}

void StageIntro::reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode( GL_PROJECTION);

	glLoadIdentity();

	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble) height;

	gluPerspective(90, aspect, 1.0, 5.0);
}

void StageIntro::performMouseMove(int x, int y)
{

}

void StageIntro::drawAll()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_MODELVIEW);

	glClear( GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera::setStaticVision();

	StringDrawer::drawString("press SPACE to continue...", -0.5, -2.6f, 0, GLUT_BITMAP_HELVETICA_10, flickeringColor->getColor());

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, logo->mTextureID);
	glColor4fv(Colors::White);

	glBegin(GL_QUADS);

	//glTexCoord2f(0.0, 0.0);
	glTexCoord2f(0.01, 0.01);
	glVertex3f(-3, 2.25f, 0); //upper left
	//glTexCoord2f(1.0, 0.0);
	glTexCoord2f(0.99, 0.01);
	glVertex3f(3, 2.25f, 0); //upper right
	//glTexCoord2f(1.0, 1.0);
	glTexCoord2f(0.99, 0.99);
	glVertex3f(3, -2.25f, 0); //bottom right
	//glTexCoord2f(0.0, 1.0);
	glTexCoord2f(0.01, 0.99);
	glVertex3f(-3, -2.25f, 0); //bottom left

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glFlush();

	glutSwapBuffers();
}
