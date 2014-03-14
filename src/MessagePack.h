/*
 * MessagePack.h
 *
 *  Created on: Aug 27, 2013
 *      Author: lucas
 */

#ifndef MESSAGEPACK_H_
#define MESSAGEPACK_H_

#include "BrickProperties.h"

class IMessager;

struct Direction{
	static const int RIGHT = 2;
	static const int LEFT = 4;
	static const int UP = 1;
	static const int DOWN = 3;
	static const int NONE = 0;
};



namespace Message{

enum Type{
	MOVE_DATA = 1,
	MOVE_REQUEST,
	ADD_BRICK,
	REQUEST_DIRECTION,
	REQUEST_REAL_POSITION,
	SET_REAL_POSITION,
	COLLISION_NOTIFICATION,
	BOOST_ADD,
	SIMPLE_NOTIFICATION,
	ADD_POINTS,

};

enum Notification{
	KILL = 100,
	DISPOSE_ME_REQUEST,
	PLAYER_1_DEAD,
	BOOST_OBTAINED_JUMP,
	BOOST_OBTAINED_SPEED,
	BOOST_USED,
};

enum BoostType{
	NONE = 1000,
	CHANGE_LENGHT,
	BOOST_SPEED,
	BOOST_JUMP,
};

enum Player{
	PLAYER_1 = 10000,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4,
	PLAYER_NONE
};


struct MessagePack {
protected:
	MessagePack(long int sid, Type type);

public:
	virtual void reset() = 0;
	Type msgType;
	long int senderID;
	virtual ~MessagePack();
};

struct ControlInfo : public MessagePack{
public:
	ControlInfo(long int sid);
	void reset();
	short glutKey;
	char key;
};

struct MoveRequest : public MessagePack{
public:
	MoveRequest(long int sid , BrickProperties headp , int directionp);
	void reset();
	BrickProperties head;
	int direction;
};

struct ChangeMoveDirectionRequest: public MessagePack{
public:

	ChangeMoveDirectionRequest(long int sid , int directionp);
	int direction;
	void reset();
};

struct AddBrick : public MessagePack{
public:
	AddBrick(long int sid , BrickProperties newHeadp);
	BrickProperties newHead;
	void reset();
};

struct GetRealPosition : public MessagePack{
public:
	GetRealPosition(long int sid , Vector4f headp);
	Vector4f head;
	void reset();
};

struct SetRealPosition : public MessagePack{
public:
	SetRealPosition(long int sid , Vector3f pos);
	Vector3f realPosition;
	void reset();
};

struct CollisionNotification : public MessagePack{
public:
	CollisionNotification(long int sid , IMessager* object);
	IMessager* otherObject;
	void reset();
};

struct AddBoost : public MessagePack{
	AddBoost(long int sid , BoostType bType , int val);
	void reset();

	BoostType boostType;
	int value;
};

struct SimpleNotification : public MessagePack{
	SimpleNotification(long int sid , Notification notif);

	void reset();
	Notification notification;
};

struct AddPoints : public MessagePack{
	AddPoints( long sid , Player playerNR , int _points );

	void reset();

	int points;
	Player playerNr;
};
}

#endif /* MESSAGEPACK_H_ */
