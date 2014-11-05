#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "MapObject.h"

class Obstacle: public MapObject
{
	public:
		Obstacle();
		virtual ~Obstacle();

		//@override
		void update(int mili);
		//@override
		void giveMessage(Message::MessagePack*);
		//@override
		void init()
		{
		}
		;

	private:
		int innerTimer;
};

#endif /* OBSTACLE_H_ */
