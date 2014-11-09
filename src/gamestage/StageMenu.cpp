#include "StageMenu.h"


#include <boost/foreach.hpp>

#include "../Camera.h"

#include "GameStateManager.h"

#include "../gui/StringDrawer.h"
#include "../Colors.h"
#include "../StringHandler.h"

#include <algorithm>

StageMenu::StageMenu()
{
	highscoreHandler = new HighscoreHandler();
	highscores = std::vector<TextInFrame>();
}

StageMenu::~StageMenu()
{
	delete highscoreHandler;
}

void StageMenu::init()
{
	initHighScores();
}

void StageMenu::close()
{
	highscoreHandler->saveAll();
}

void StageMenu::performKeyboardInput(unsigned char key, int x, int y)
{
	if ((int) key < 97)
		key += 32;

	switch (key)
	{
		case 'p':
			GameStateManager::startGameState();
			break;
		case 'q':
			exit(EXIT_SUCCESS);
		default:
			break;
	}
}

void StageMenu::performSpecialKeyboardInput(int key, int x, int y)
{

}

void StageMenu::performMouseDragg(int x, int y)
{

}

void StageMenu::initHighScores()
{
	highscoreHandler->loadAll();

	if (GameStateManager::getProperty(Properties::NEW_HIGHSCORE_INDICATOR).compare("true") == 0)
	{
		GameStateManager::setProperty(Properties::NEW_HIGHSCORE_INDICATOR, "false");
		highscoreHandler->add(Highscore(GameStateManager::getProperty(Properties::PLAYER_NAME), GameStateManager::getProperty(Properties::NEW_HIGHSCORE_VALUE)));
		highscoreHandler->saveAll();
	}

	const float* actColor;

	highscores.push_back(TextInFrame(Vector3f( -0.3f, 1.9f , 0), Vector2f(4, 0.3),"                     highscores", Colors::Gray ));

	int innerCounter = 0;
	BOOST_FOREACH(Highscore highscore, highscoreHandler->getHighscores())
	{
		switch(innerCounter)
		{
			case 0: actColor = Colors::Gold; break;
			case 1: actColor = Colors::Silver; break;
			case 2: actColor = Colors::Bronze; break;
			default: actColor = Colors::Aqua;
		}

		highscores.push_back(TextInFrame(Vector3f( -0.3f, 1.5f - (innerCounter * 0.4), 0), Vector2f(4, 0.3),highscore.getName(), actColor ));
		highscores.push_back(TextInFrame(Vector3f( 2.3, 1.5f - (innerCounter * 0.4), 0), Vector2f(1, 0.3),highscore.getResult(), actColor ));
		++innerCounter;
	}
}

void StageMenu::performMouseAction(int button, int state, int x, int y)
{

}

void StageMenu::reshape(int width, int height)
{
	// obszar renderingu - całe okno
	glViewport(0, 0, width, height);

	// wybór macierzy rzutowania
	glMatrixMode( GL_PROJECTION);

	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();

	// obliczenie aspektu obrazu z uwzględnieniem
	// przypadku, gdy wysokość obrazu wynosi 0
	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble) height;

	// rzutowanie perspektywiczne
	gluPerspective(90, aspect, 1.0, 5.0);
}

void StageMenu::performMouseMove(int x, int y)
{

}

GAME_STAGE::GAME_STAGE StageMenu::getGameStageEnum()
{
	return GAME_STAGE::MENU;
}

void StageMenu::drawAll()
{
	static const std::string stringStart = "[P]lay";
	static const std::string stringQuit = "[Q]uit";

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_MODELVIEW);

	glLoadIdentity();

	//gluLookAt(0., 0., 3., 0., 0., 0., 0., 1., 0.);

	Camera::setStaticVision();

	BOOST_FOREACH(TextInFrame tif, highscores)
	{
		tif.draw();
	}

	glEnable( GL_DEPTH_TEST);
	/*****<OBJECT DRAWING>*******/
	StringDrawer::drawString(stringStart, -2.5, 2.2, 0.);
	StringDrawer::drawString(stringQuit, -2.5, 1.8, 0.);
	/*****</OBJECT DRAWING>*******/

	glFlush();

	glutSwapBuffers();
}

void StageMenu::update()
{
	StageMenu::drawAll();
}


