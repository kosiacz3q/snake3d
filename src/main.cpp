#include <GL/freeglut.h>
#include <IL/il.h>

#include "gamestage/GameStateManager.h"


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(250, 100);

	glDisable(GL_ALL_ATTRIB_BITS);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GREATER);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glutCreateWindow("Snake3D");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

	ilInit();
	ilClearColour(255, 255, 255, 000);

	GameStateManager::init();
	GameStateManager::startIntroState();
	//GameStateManager::setProperty("colorPerWall" , "yes");
	GameStateManager::setProperty(Properties::PLAYER_NAME , "kosiacz3q");
	glutMainLoop();
	GameStateManager::close();

	return 0;
}
