#include "Gainer.h"

Gainer::Gainer(Message::BoostType boostType, int val)
		: MapObject(GAINER)
{
	this->boostType = boostType;
	this->value = val;
	innerTimer = 0;
	collapsingTimer = 0; //TODO add collapsing effect
}

Gainer::~Gainer()
{

}

void Gainer::giveMessage(Message::MessagePack* msg)
{

	switch (msg->msgType)
	{
		case Message::COLLISION_NOTIFICATION:
		{
			Message::CollisionNotification* mc = (Message::CollisionNotification*) msg;
			mc->otherObject->giveMessage(new Message::AddBoost(this->ID, this->boostType, this->value));
		}
			break;

		case Message::SIMPLE_NOTIFICATION:
		{
			if (((Message::SimpleNotification*) msg)->notification == Message::KILL)
			{
				hitable = false;
			}
		}
			break;

		default:
			break;
	}

	delete msg;
}

void Gainer::update(int miliseconds)
{

	innerTimer += miliseconds;

	if (!hitable)
	{
		if (collapsingTimer >= 0)
		{
			collapsingTimer -= miliseconds;
		}
		else
		{
			this->parent->giveMessage(new Message::SimpleNotification(this->ID, Message::DISPOSE_ME_REQUEST));
		}
	}
	else if (innerTimer >= jumpInterval)
	{
		if (this->tail.begin()->position.z > 0)
		{
			--this->tail.begin()->position.z;
		}
		innerTimer -= jumpInterval;
	}
}
