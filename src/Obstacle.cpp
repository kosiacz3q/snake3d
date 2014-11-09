#include "Obstacle.h"
#include "gamestage/GameStateManager.h"

Obstacle::Obstacle()
		: MapObject(OBSTACLE)
{
	innerTimer = 0;
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(int mili)
{
	innerTimer += mili;

	if (innerTimer >= 1000)
	{
		if (this->tail.begin()->position.z > 0)
		{
			--this->tail.begin()->position.z;
		}
		innerTimer -= 1000;
	}
}

void Obstacle::giveMessage(Message::MessagePack* msg)
{
	switch (msg->msgType)
	{
		case Message::COLLISION_NOTIFICATION:
		{
			Message::CollisionNotification* mc = (Message::CollisionNotification*) msg;
			mc->otherObject->giveMessage(new Message::SimpleNotification(this->ID, Message::KILL));
			GameStateManager::setProperty(Properties::DEATH_CAUSE , "You hit a fucking wall");
		}
			break;


		case Message::SIMPLE_NOTIFICATION:
		{
			if (((Message::SimpleNotification*) msg)->notification == Message::KILL)
				this->parent->giveMessage(new Message::SimpleNotification(this->ID, Message::DISPOSE_ME_REQUEST));
		}
			break;

		default:
			break;
	}

	delete msg;
}
