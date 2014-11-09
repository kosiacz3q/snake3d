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
	pointsCounter =  nullptr;
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

	mainBrick->controlInfo->key = key;

	switch (key)
	{
		case 'a':
			mainBrick->controlInfo->glutKey = GLUT_KEY_LEFT;
			break;

		case 'w':
			mainBrick->controlInfo->glutKey = GLUT_KEY_UP;
			break;

		case 'd':
			mainBrick->controlInfo->glutKey = GLUT_KEY_RIGHT;
			break;

		case 's':
			mainBrick->controlInfo->glutKey = GLUT_KEY_DOWN;
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

	mainBrick->controlInfo->glutKey = (short) key;

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
	GameStateManager::setProperty(Properties::NEW_HIGHSCORE_VALUE , boost::lexical_cast<std::string>(pointsCounter->getValue()));

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

	dataConnector = 0;

}

void StageGame::init()
{
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

			Gainer* gainer;

			int num = RandomPositionGenerator::getRandomNumber(0, 7);

			switch (num)
			{
				case 0:
					gainer = new Gainer(Message::BOOST_SPEED, 20);
					gainer->tail.push_back(BrickProperties(RandomPositionGenerator::generate(mainBrick->wallDim, -1, 5, 20, 0), Colors::Red));
					break;
				case 7:
					gainer = new Gainer(Message::BOOST_JUMP, 20);
					gainer->tail.push_back(BrickProperties(RandomPositionGenerator::generate(mainBrick->wallDim, -1, 5, 20, 0), Colors::Blue));
					break;

				default:
					gainer = new Gainer(Message::CHANGE_LENGHT, 1);
					gainer->tail.push_back(BrickProperties(RandomPositionGenerator::generate(mainBrick->wallDim, -1, 5, 20, 0), Colors::Goldenrod));
					break;

			}

			;
			mainBrick->addMapObject(gainer);
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
	mainBrick = new MainBrick();
	mainBrick->setParent(dataConnector);
	mainBrick->mainBrick->color_normal_vertex = new float[80];
	mainBrick->mainBrick->indexTable = new GLubyte[36];
	mainBrick->objectsBrick->color_normal_vertex = new float[80];
	mainBrick->objectsBrick->indexTable = new GLubyte[36];
	mainBrick->mainBrick->setPosition(Vector3f(0., 0., 0.));
	ShapeGenerator::getSquare(mainBrick->mainBrick->color_normal_vertex, 2.1, Colors::Aqua);
	mainBrick->halfOfMainBrick = 1.05;
	ShapeGenerator::getSquare(mainBrick->objectsBrick->color_normal_vertex, .1, Colors::HotPink);
	mainBrick->halfOfObjectsBrick = .05;
	mainBrick->objectsBrickDimm = .1;
	ShapeGenerator::setStandartSquareIndexTable(mainBrick->mainBrick->indexTable);
	ShapeGenerator::setStandartSquareIndexTable(mainBrick->objectsBrick->indexTable);
	ShapeGenerator::LSDonGL_C4F_N3F_V3F(mainBrick->mainBrick->color_normal_vertex, 8);

	mainBrick->wallDim = new int*[6];
	for (int i = 0; i < 6; ++i)
		mainBrick->wallDim[i] = new int[4]; //width height centerX  centerY

	mainBrick->wallDim[0][0] = 23; //x max
	mainBrick->wallDim[0][1] = 23; //y max
	mainBrick->wallDim[0][2] = 12 - 1; // x center
	mainBrick->wallDim[0][3] = 12 - 1; // y center

	mainBrick->wallDim[1][0] = 21;
	mainBrick->wallDim[1][1] = 23;
	mainBrick->wallDim[1][2] = 11 - 1;
	mainBrick->wallDim[1][3] = 12 - 1;

	mainBrick->wallDim[2][0] = 23;
	mainBrick->wallDim[2][1] = 23;
	mainBrick->wallDim[2][2] = 12 - 1;
	mainBrick->wallDim[2][3] = 12 - 1;

	mainBrick->wallDim[3][0] = 21;
	mainBrick->wallDim[3][1] = 23;
	mainBrick->wallDim[3][2] = 11 - 1;
	mainBrick->wallDim[3][3] = 12 - 1;

	mainBrick->wallDim[4][0] = 21;
	mainBrick->wallDim[4][1] = 21;
	mainBrick->wallDim[4][2] = 11 - 1;
	mainBrick->wallDim[4][3] = 11 - 1;

	mainBrick->wallDim[5][0] = 21;
	mainBrick->wallDim[5][1] = 21;
	mainBrick->wallDim[5][2] = 11 - 1;
	mainBrick->wallDim[5][3] = 11 - 1;

	playerSnake = new SnakeBody(Vector4f(11, 11, 0, 1));
	mainBrick->snakeID = playerSnake->getID();
	mainBrick->addMapObject(playerSnake);

	Obstacle* obstacle;
	for (int i = 0; i < 10; ++i)
	{
		obstacle = new Obstacle();
		obstacle->tail.push_back(BrickProperties(RandomPositionGenerator::generate(mainBrick->wallDim, -1, 5, 20, i * 5), Colors::Black));
		mainBrick->addMapObject(obstacle);
	}
}

void StageGame::performMouseDragg(int x, int y)
{
	mouse.setMousePosition(x, y);

	mainBrick->mainBrick->rotation.x -= (mouse.lastPosition.x - mouse.actualPosition.x);
	mainBrick->mainBrick->rotation.y -= (mouse.lastPosition.y - mouse.actualPosition.y);
}

void StageGame::performMouseAction(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		mouse.leftButtonState = state;
	else if (button == GLUT_RIGHT_BUTTON)
		mouse.rightButtonState = state;

	mouse.setMousePosition(x, y);
}

void StageGame::performMouseMove(int x, int y)
{
	mouse.setMousePosition(x, y);
}
