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

		void giveMessage(Message::MessagePack*);

	private:
		Message::BoostType boostType;
		int value;

		int collapsingTimer;
		int innerTimer;
		static const int jumpInterval = 700;
};

#endif /* GAINER_H_ */
