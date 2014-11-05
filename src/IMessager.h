#ifndef IMESSAGER_H_
#define IMESSAGER_H_

#include "MessagePack.h"

class IMessager
{
	public:
		virtual ~IMessager();

		virtual void giveMessage(Message::MessagePack*) = 0;
};

#endif /* IMESSAGER_H_ */
