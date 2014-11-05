#ifndef GAINER_H_
#define GAINER_H_

#include "MapObject.h"

class Gainer: public MapObject
{
	public:
		Gainer(Message::BoostType boostType, int val);
		virtual ~Gainer();

		void init()
		{
		}
		;

		void update(int miliseconds);

		//@override
		void giveMessage(Message::MessagePack*);
		Message::BoostType boostType;
		int value;
	private:
		int collapsingTimer;
		int innerTimer;
		static const int jumpInterval = 700;
};

#endif /* GAINER_H_ */
