#ifndef GAME_H
#define GAME_H
#include <map>

#include "../Camera.h"
#include "../MainBrickHandler.h"
#include "../MouseHandler.h"
#include "../RotaryCounter.h"
#include "../SnakeAbilities.h"
#include "GameStage.h"

typedef ::std::map<int, Object*> ObjectContainer;

class StageGame : public GameStage
{
	public:
		StageGame();

		void init();
		void close();
		void update();

		GAME_STAGE::GAME_STAGE getGameStageEnum();

		class DataConnector: public IMessager
		{
			public:
				DataConnector(StageGame* parent)
					:parent(parent){}
				void giveMessage(Message::MessagePack*);

			private:
				StageGame* parent;
		};

		DataConnector* dataConnector;

		void drawAll();
		void performlogic();
		void performKeyboardInput(unsigned char key, int x, int y);
		void performSpecialKeyboardInput(int key, int x, int y);
		void performMouseDragg(int x, int y);
		void performMouseAction(int button, int state, int x, int y);
		void reshape(int width, int height);

		void performMouseMove(int x, int y);
		void initObjects();

	private:
		MainBrickHandler* mainBrick;
		SnakeBody* playerSnake;
		SnakeAbilities* abilitiesIndicator;
		boost::posix_time::ptime lastUpdate;
		int acumulatedMiliseconds_objectSpawn;
		RotaryCounter* pointsCounter;
		ObjectContainer gameObjects;
		MouseHandler mouse;
};

#endif // GAME_H
