#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "MapObject.h"

class Obstacle: public MapObject
{
	public:
		Obstacle();
		virtual ~Obstacle();

		void update(int mili);

		void giveMessage(Message::MessagePack*);

		void init()
		{
		}
		;

	private:
		int innerTimer;
};

#endif /* OBSTACLE_H_ */
