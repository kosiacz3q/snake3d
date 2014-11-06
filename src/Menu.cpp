#include "Menu.h"

#include <GL/glut.h>
#include <boost/foreach.hpp>

#include "Camera.h"
#include "GameStateManager.h"
#include "Colors.h"

HighscoreHandler* Menu::highscoreHandler = nullptr;

Menu::Menu()
{

}

void Menu::init()
{
	glutReshapeFunc(Menu::reshape);
	glutKeyboardFunc(Menu::performKeyboardInput);
	glutSpecialFunc(Menu::performSpecialKeyboardInput);
	glutMouseFunc(Menu::performMouseAction);
	glutMotionFunc(Menu::performMouseDragg);
	glutPassiveMotionFunc(Menu::performMouseMove);
	glutIdleFunc(Menu::update);

	highscoreHandler = new HighscoreHandler();
	highscoreHandler->loadAll();
}

void Menu::close()
{
	highscoreHandler->saveAll();
	delete highscoreHandler;
}

void Menu::performKeyboardInput(unsigned char key, int x, int y)
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

void Menu::performSpecialKeyboardInput(int key, int x, int y)
{

}

void Menu::performMouseDragg(int x, int y)
{

}

void Menu::performMouseAction(int button, int state, int x, int y)
{

}

void Menu::reshape(int width, int height)
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

void Menu::performMouseMove(int x, int y)
{

}

void Menu::drawAll()
{
	static const std::string stringStart = "[P]lay";
	static const std::string stringQuit = "[Q]uit";


	// kolor tła - zawartość bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode( GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	gluLookAt(0., 0., 3., 0., 0., 0., 0., 1., 0.);

	int innerCounter = 0;
	BOOST_FOREACH(Highscore highscore, highscoreHandler->getHighscores())
	{
		drawString(highscore.getName().c_str(), highscore.getName().length(), 0.3, 0.2 - (innerCounter * 0.2), 0.);
		drawString(highscore.getResult().c_str(), highscore.getResult().length(), 2.5, 0.2 - (innerCounter * 0.2), 0.);
		++innerCounter;
	}

	glEnable( GL_DEPTH_TEST);
	/*****<OBJECT DRAWING>*******/
	drawString(stringStart.c_str(), stringStart.length(), -2.5, 2.2, 0.);
	drawString(stringQuit.c_str(), stringQuit.length(), -2.5, 1.8, 0.);
	/*****</OBJECT DRAWING>*******/

	glFlush();

	glutSwapBuffers();
}



void Menu::update()
{
	Menu::drawAll();
}

void Menu::drawString(const char* seq, int length, const float x, const float y, const float z)
{

	glColor4fv(Colors::DarkBlue);

	glRasterPos3f((GLfloat) x, (GLfloat) y, (GLfloat) z);

	for (int i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, seq[i]);
	}
}
