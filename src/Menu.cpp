#include "Menu.h"

#include <GL/glut.h>
#include "Camera.h"
#include "GameStateManager.h"
#include "Colors.h"

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
}

void Menu::close()
{

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
	// kolor tła - zawartość bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// czyszczenie bufora koloru
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybór macierzy modelowania
	glMatrixMode( GL_MODELVIEW);

	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();

	gluLookAt(0., 0., 3., 0., 0., 0., 0., 1., 0.);

	glEnable( GL_DEPTH_TEST);
	/*****<OBJECT DRAWING>*******/
	drawString("[p]lay", 6, -0.5, 0.2, 0.);
	drawString("[q]uit", 6, -0.5, -0.2, 0.);
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
