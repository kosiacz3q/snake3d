#ifndef MAINBRICK_H_
#define MAINBRICK_H_

#include <map>
#include <vector>

#include "Brick.h"
#include "SnakeBody.h"
#include "Obstacle.h"
#include "Gainer.h"

typedef std::map<int, MapObject*> MapObjects;
typedef std::vector<Message::MessagePack*> MessagesVector;

class MainBrickHandler: public IMessager
{
	public:
		MainBrickHandler();
		virtual ~MainBrickHandler();

		void drawAll();
		void updateAll(int time);

		void addMapObject(MapObject* obj);
		void removeMapObject(int id);

		//@override
		void giveMessage(Message::MessagePack*);

		void setParent(IMessager* parent)
		{
			this->parent = parent;
		}

		void init();

		void setSnakeId(long int id);

		void addObstacle(int count = 1);
		void addGainers(Message::BoostType type,int count = 1);

		Message::ControlInfo* getControlInfo()
		{
			return controlInfo;
		}

	private:
		Brick* mainBrick;
		Brick* objectsBrick;
		int** wallDim;
		Message::ControlInfo* controlInfo;
		int snakeID;

		MapObjects objects;
		MessagesVector messages;
		IMessager* parent;
		int translationTab[5];

		void detectCollisions();

		/*****DIRECTION TRANSLATION HANDLERS**********/
		void clockwiseTranslate();
		void counterclockwiseTranslate();
};

#endif /* MAINBRICK_H_ */
