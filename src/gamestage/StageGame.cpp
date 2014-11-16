#include "StageGame.h"

#include "../ShapeGenerator.h"
#include "../Colors.h"
#include "../RandomPositionGenerator.h"
#include "GameStateManager.h"

StageGame::StageGame()
{
	gameObjects = ObjectContainer();
	mouse = MouseHandler();
	mainBrick = nullptr;
	playerSnake = nullptr;
	acumulatedMiliseconds_objectSpawn = 0;
	pointsCounter = nullptr;
	dataConnector = nullptr;
	abilitiesIndicator = nullptr;
}

void StageGame::DataConnector::giveMessage(Message::MessagePack* msg)
{
	if (msg->msgType == Message::ADD_POINTS)
	{
		parent->pointsCounter->addPoints(((Message::AddPoints*) msg)->points);
	}
	else if (msg->msgType == Message::SIMPLE_NOTIFICATION)
	{
		parent->abilitiesIndicator->setActiveAbility(((Message::SimpleNotification*) msg)->notification);
	}
}

void StageGame::drawAll()
{

	if (mainBrick != 0)
	{
		glClearColor(1.0, 1.0, 1.0, 1.0);

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode( GL_MODELVIEW);

		glLoadIdentity();
		glEnable( GL_DEPTH_TEST);
		Camera::setVision();
		mainBrick->drawAll();

		glClear( GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		//glDisable( GL_DEPTH_TEST);

		Camera::setStaticVision();

		pointsCounter->draw();
		abilitiesIndicator->draw();

		glFlush();

		glutSwapBuffers();
	}
}

void StageGame::performlogic()
{

}

GAME_STAGE::GAME_STAGE StageGame::getGameStageEnum()
{
	return GAME_STAGE::GAME;
}

void StageGame::performKeyboardInput(unsigned char key, int x, int y)
{

	if ((int) key < 97)
		key += 32;

	mainBrick->getControlInfo()->key = key;

	switch (key)
	{
		case 'a':
			mainBrick->getControlInfo()->glutKey = GLUT_KEY_LEFT;
			break;

		case 'w':
			mainBrick->getControlInfo()->glutKey = GLUT_KEY_UP;
			break;

		case 'd':
			mainBrick->getControlInfo()->glutKey = GLUT_KEY_RIGHT;
			break;

		case 's':
			mainBrick->getControlInfo()->glutKey = GLUT_KEY_DOWN;
			break;
		case 'q':
			GameStateManager::startMenuState();
			break;
		default:
			break;
	}

}

void StageGame::performSpecialKeyboardInput(int key, int x, int y)
{

	mainBrick->getControlInfo()->glutKey = (short) key;

}

void StageGame::reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode( GL_PROJECTION);

	glLoadIdentity();

	GLdouble aspect = 1;
	if (height > 0)
		aspect = width / (GLdouble) height;

	gluPerspective(90, aspect, 1.0, 5.0);
}

void StageGame::close()
{
	GameStateManager::setProperty(Properties::NEW_HIGHSCORE_VALUE, boost::lexical_cast<std::string>(pointsCounter->getValue()));

	delete mainBrick;
	mainBrick = nullptr;
	for (ObjectContainer::iterator iter = gameObjects.begin(); iter != gameObjects.end(); ++iter)
	{
		delete iter->second;
	}

	SnakeAbilities::free();
	RotaryCounter::free();

	delete pointsCounter;
	delete dataConnector;
	delete abilitiesIndicator;

	dataConnector = nullptr;
}

void StageGame::init()
{
	glutSetCursor(GLUT_CURSOR_NONE);
	Camera::reset();
	Camera::setPosition(Vector3f(0., 0., 3.));

	lastUpdate = boost::posix_time::microsec_clock::local_time();

	RandomPositionGenerator::clearReservedPosition();

	initObjects();
}

void StageGame::update()
{

	boost::posix_time::ptime actual = boost::posix_time::microsec_clock::local_time();

	boost::posix_time::time_duration diff = actual - lastUpdate;

	mainBrick->updateAll(diff.total_milliseconds());

	if (mainBrick != nullptr)
	{
		pointsCounter->update(diff.total_milliseconds());
		acumulatedMiliseconds_objectSpawn += diff.total_milliseconds();

		lastUpdate = actual;

		if (acumulatedMiliseconds_objectSpawn >= 1000)
		{
			switch (RandomPositionGenerator::getRandomNumber(0, 30))
			{
				case 0:
				case 1:
				case 2:
					mainBrick->addGainers(Message::BOOST_SPEED);
					break;

				case 15:
				case 16:
				case 17:
					mainBrick->addGainers(Message::BOOST_JUMP);
					break;

				case 25:
				case 26:
					mainBrick->addObstacle();
					break;

				default:
					mainBrick->addGainers(Message::CHANGE_LENGHT);
			}

			acumulatedMiliseconds_objectSpawn -= 1000;
		}

		performlogic();
		drawAll();
	}

}

void StageGame::initObjects()
{

	dataConnector = new DataConnector(this);
	Vector3f pos = Vector3f(-3.5, -2, 0.);
	pointsCounter = new RotaryCounter(pos);
	pointsCounter->setRotation(Vector3f(60, 55, 0));

	abilitiesIndicator = new SnakeAbilities(Vector3f(2.5, -1.8, 0.));
	abilitiesIndicator->setRotation(Vector3f(-50., -30, 0));
	SnakeAbilities::init();

	//Main Brick
	mainBrick = new MainBrickHandler();
	mainBrick->setParent(dataConnector);

	mainBrick->init();

	playerSnake = new SnakeBody(Vector4f(11, 11, 0, 1));
	mainBrick->setSnakeId(playerSnake->getID());
	mainBrick->addMapObject(playerSnake);

	mainBrick->addObstacle(10);
}

void StageGame::performMouseDragg(int x, int y)
{
	//mouse.setMousePosition(x, y);

	//mainBrick->mainBrick->rotation.x -= (mouse.lastPosition.x - mouse.actualPosition.x);
	//mainBrick->mainBrick->rotation.y -= (mouse.lastPosition.y - mouse.actualPosition.y);
}

void StageGame::performMouseAction(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		mouse.setLeftButtonState(state);
	else if (button == GLUT_RIGHT_BUTTON)
		mouse.setRightButtonState(state);

	mouse.setMousePosition(x, y);
}

void StageGame::performMouseMove(int x, int y)
{
	mouse.setMousePosition(x, y);
}
