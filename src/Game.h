#ifndef GAME_H
#define GAME_H
#include <map>

#include "MainBrick.h"
#include "Camera.h"
#include "MouseHandler.h"
#include "RotaryCounter.h"
#include "SnakeAbilities.h"

typedef ::std::map<int, Object*> ObjectContainer;

class Game
{
	public:
		static void init();
		static void close();

		class DataConnector: public IMessager
		{
			public:
				void giveMessage(Message::MessagePack*);
		};

		static DataConnector* dataConnector;

	protected:

	private:
		static void drawAll();
		static void performlogic();
		static void performKeyboardInput(unsigned char key, int x, int y);
		static void performSpecialKeyboardInput(int key, int x, int y);
		static void performMouseDragg(int x, int y);
		static void performMouseAction(int button, int state, int x, int y);
		static void reshape(int width, int height);
		static ObjectContainer gameObjects;
		static MouseHandler mouse;
		static void performMouseMove(int x, int y);
		static void initObjects();
		static void update();

		Game();
		static MainBrick* mainBrick;
		static SnakeBody* playerSnake;
		static SnakeAbilities* abilitiesIndicator;
		static boost::posix_time::ptime lastUpdate;
		static int acumulatedMiliseconds_objectSpawn;
		static RotaryCounter* pointsCounter;
};

#endif // GAME_H
