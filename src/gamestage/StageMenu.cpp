#include "StageMenu.h"

#include <boost/foreach.hpp>
#include <cstdio>

#include "../Camera.h"
#include "GameStateManager.h"
#include "../gui/StringDrawer.h"
#include "../Colors.h"
#include "../StringHandler.h"

StageMenu::StageMenu()
		: lastMousePositon(Vector2f(0, 0)), _changngNameInProgress(false)
{
	highscoreHandler = new HighscoreHandler();
	highscores = std::vector<TextInFrame>();
	mouseRotator = new SelfStabilizingRotator();
	_buttonPlay = new SelectableTexturedButton(Vector3f(-3.5, 2.0f, 0), Vector2f(2, 0.3f), "tex/button_play.png", Colors::LightGreen);
	_buttonName = new SelectableTexturedButton(Vector3f(-3.5, 1.0f, 0), Vector2f(2, 0.3f), "tex/button_name.png", Colors::LightGreen);
	_buttonQuit = new SelectableTexturedButton(Vector3f(-3.5, 0.0f, 0), Vector2f(2, 0.3f), "tex/button_quit.png", Colors::LightCoral);
}

StageMenu::~StageMenu()
{
	delete highscoreHandler;
	delete mouseRotator;
}

void StageMenu::init()
{
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	initHighScores();
	GameStateManager::setProperty(Properties::PLAYER_NAME, highscoreHandler->getUsername());
	_tempName = GameStateManager::getProperty(Properties::PLAYER_NAME);
}

void StageMenu::close()
{
	delete _buttonPlay;
	delete _buttonQuit;
	delete _buttonName;
	highscoreHandler->saveAll();
}

void StageMenu::performKeyboardInput(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		_tempName.clear();
		endChangeNameState();
	}
	else if (key == 13)
	{
		endChangeNameState();
	}
	else if (_changngNameInProgress)
	{
		if (key == 8)
		{
			if (!_tempName.empty())
			{
				_tempName.erase(_tempName.end() - 1);
			}
		}
		else if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122))
		{
			_tempName += key;
		}
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
		highscoreHandler->add(
				Highscore(GameStateManager::getProperty(Properties::PLAYER_NAME), GameStateManager::getProperty(Properties::NEW_HIGHSCORE_VALUE)));
		highscoreHandler->saveAll();
	}

	const float* actColor;

	highscores.push_back(TextInFrame(Vector3f(-0.3f, 1.9f, 0), Vector2f(4, 0.3), "                     highscores", Colors::Gray));

	int innerCounter = 0;
	BOOST_FOREACH(Highscore highscore, highscoreHandler->getHighscores())
	{
		switch (innerCounter)
		{
			case 0:
				actColor = Colors::Gold;
				break;
			case 1:
				actColor = Colors::Silver;
				break;
			case 2:
				actColor = Colors::Bronze;
				break;
			default:
				actColor = Colors::Aqua;
		}

		highscores.push_back(TextInFrame(Vector3f(-0.3f, 1.5f - (innerCounter * 0.4), 0), Vector2f(4, 0.3), highscore.getName(), actColor));
		highscores.push_back(TextInFrame(Vector3f(2.3, 1.5f - (innerCounter * 0.4), 0), Vector2f(1, 0.3), highscore.getResult(), actColor));
		++innerCounter;
	}
}

void StageMenu::performMouseAction(int button, int state, int x, int y)
{
	int id = pick(x, y);

	if (_buttonPlay->getId() == id)
	{
		GameStateManager::startGameState();
	}

	if (_buttonName->getId() == id)
	{
		startChangeNameState();
	}

	if (_buttonQuit->getId() == id)
	{
		exit(EXIT_SUCCESS);
	}
}

void StageMenu::reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode( GL_PROJECTION);

	glLoadIdentity();

	if (height > 0)
		aspect = width / (GLdouble) height;

	gluPerspective(90, aspect, 1.0, 5.0);
}

void StageMenu::performMouseMove(int x, int y)
{
	mouseRotator->addYRotation((lastMousePositon.x - x) / 50);
	mouseRotator->addXRotation((lastMousePositon.y - y) / 50);

	lastMousePositon.x = x;
	lastMousePositon.y = y;

	if (_changngNameInProgress)
	{
		_buttonName->setSelected(true);
		return;
	}

	int id = pick(x, y);

	if (_buttonPlay->getId() == id)
	{
		_buttonPlay->setSelected(true);
	}
	else
	{
		_buttonPlay->setSelected(false);
	}

	if (_buttonQuit->getId() == id)
	{
		_buttonQuit->setSelected(true);
	}
	else
	{
		_buttonQuit->setSelected(false);
	}

	if (_buttonName->getId() == id)
	{
		_buttonName->setSelected(true);
	}
	else
	{
		_buttonName->setSelected(false);
	}
}

GAME_STAGE::GAME_STAGE StageMenu::getGameStageEnum()
{
	return GAME_STAGE::MENU;
}

void StageMenu::drawAll()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_MODELVIEW);

	glLoadIdentity();

	Camera::setStaticVision();

	glPushMatrix();
	mouseRotator->applyRotation();

	BOOST_FOREACH(TextInFrame tif, highscores)
	{
		tif.draw();
	}

	glPopMatrix();

	glEnable( GL_DEPTH_TEST);
	/*****<OBJECT DRAWING>*******/
	_buttonPlay->draw();
	_buttonQuit->draw();
	_buttonName->draw();

	glPushMatrix();
	StringDrawer::drawString(_tempName, -2.5 - _tempName.size() * 0.05, 0.8f, 0.1f, GLUT_BITMAP_TIMES_ROMAN_24, Colors::DarkGreen);
	glPopMatrix();

	glFlush();

	glutSwapBuffers();
}

void StageMenu::startChangeNameState()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	_changngNameInProgress = true;
}

void StageMenu::endChangeNameState()
{
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	_changngNameInProgress = false;
	_buttonName->setSelected(false);

	if (!_tempName.empty())
	{
		highscoreHandler->setUsername(_tempName);
		GameStateManager::setProperty(Properties::PLAYER_NAME, _tempName);
	}
	else
		_tempName = GameStateManager::getProperty(Properties::PLAYER_NAME);
}

void StageMenu::update()
{
	mouseRotator->update();
	StageMenu::drawAll();
}

int StageMenu::pick(float x, float y)
{
//START
	GLint viewport[4];
	float ratio;

	GLuint selectBuf[16];
	glSelectBuffer(16, selectBuf);

	glGetIntegerv(GL_VIEWPORT, viewport);

	glRenderMode(GL_SELECT);

	glInitNames();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix(x, viewport[3] - y, 5, 5, viewport);
	ratio = (viewport[2] + 0.0) / viewport[3];
	gluPerspective(90, ratio, 1.0, 5.0);
	glMatrixMode(GL_MODELVIEW);

//DRAW
	glLoadIdentity();

	Camera::setStaticVision();

	_buttonPlay->drawSelection();
	_buttonName->drawSelection();
	_buttonQuit->drawSelection();

//STOP
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	int hits = glRenderMode(GL_RENDER);

	if (hits > 0)
	{
		return (int) selectBuf[3];
	}

	return -1;
}

