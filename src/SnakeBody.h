#ifndef SNAKEBODY_H_
#define SNAKEBODY_H_

#include "MapObject.h"

class SnakeBody: public MapObject
{
	public:
		SnakeBody(Vector4f startPos);
		virtual ~SnakeBody();

		//@override
		void giveMessage(Message::MessagePack*);

		//@override
		void init();

		//@override
		void update(int mili);

		Vector3f headRealPos;

	private:
		long long totalMiliseconds;
		int innerTimer1;
		int jumpInterval;
		int lastDirection;
		unsigned int tailMaxLenght;
		int availableBoostType;
		int _boostTimer;
};

#endif /* SNAKEBODY_H_ */
