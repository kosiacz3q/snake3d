#include "MessagePack.h"

using namespace Message;

MessagePack::MessagePack(long int sid, Type type)
{
	msgType = type;
	senderID = sid;
}

MessagePack::~MessagePack()
{

}

ControlInfo::ControlInfo(long int sid)
		: MessagePack(sid, MOVE_DATA)
{
	key = (char) 0;
	sid = -1;
	glutKey = -1;
}

void ControlInfo::reset()
{
	key = (char) 0;
	glutKey = -1;
}

MoveRequest::MoveRequest(long int sid, BrickProperties headp, int directionp)
		: MessagePack(sid, MOVE_REQUEST)
{
	head = headp;
	direction = directionp;
}

void MoveRequest::reset()
{
	head = BrickProperties();
	direction = Direction::NONE;
}

AddBrick::AddBrick(long int sid, BrickProperties newHeadp)
		: MessagePack(sid, ADD_BRICK)
{
	newHead = newHeadp;
}

void AddBrick::reset()
{
	newHead = BrickProperties();
}

ChangeMoveDirectionRequest::ChangeMoveDirectionRequest(long int sid, int directionp)
		: MessagePack(sid, REQUEST_DIRECTION)
{
	direction = directionp;
}
void ChangeMoveDirectionRequest::reset()
{
	direction = Direction::NONE;
}

GetRealPosition::GetRealPosition(long int sid, Vector4f headp)
		: MessagePack(sid, REQUEST_REAL_POSITION)
{
	head = headp;
}

void GetRealPosition::reset()
{
	head.x = 0;
	head.w = 0;
	head.y = 0;
	head.z = 0;
}

SetRealPosition::SetRealPosition(long int sid, Vector3f pos)
		: MessagePack(sid, SET_REAL_POSITION)
{
	realPosition = pos;
}

void SetRealPosition::reset()
{
	realPosition.x = 0;
	realPosition.y = 0;
	realPosition.z = 0;
}

CollisionNotification::CollisionNotification(long int sid, IMessager* object)
		: MessagePack(sid, COLLISION_NOTIFICATION)
{
	otherObject = object;
}

void CollisionNotification::reset()
{
	otherObject = NULL;
}

AddBoost::AddBoost(long int sid, BoostType bType, int val)
		: MessagePack(sid, BOOST_ADD)
{
	value = val;
	boostType = bType;
}

void AddBoost::reset()
{
	boostType = NONE;
	value = 0;
}

SimpleNotification::SimpleNotification(long int sid, Notification notif)
		: MessagePack(sid, SIMPLE_NOTIFICATION)
{

	notification = notif;
}

void SimpleNotification::reset()
{
	//notification = 0;
}

AddPoints::AddPoints(long sid, Player playerNR, int _points)
		: MessagePack(sid, ADD_POINTS)
{
	playerNr = playerNR;
	points = _points;
}

void AddPoints::reset()
{
	playerNr = Message::PLAYER_NONE;
	points = 0;
}

