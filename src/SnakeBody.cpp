#include "SnakeBody.h"
#include "Colors.h"

SnakeBody::SnakeBody(Vector4f startPos)
		: MapObject(SNAKE)
{
	innerTimer1 = 0;
	totalMiliseconds = 0;
	jumpInterval = 150;
	lastDirection = Direction::NONE;
	tailMaxLenght = 5;
	availableBoostType = 0;
	headRealPos = Vector3f();
	_boostTimer = 0;

	tail.push_back(BrickProperties(startPos, Colors::Blue));
}

SnakeBody::~SnakeBody()
{

}

Vector3f lastReadlPosition = Vector3f();

void SnakeBody::giveMessage(Message::MessagePack* mp)
{
	switch (mp->msgType)
	{
		case Message::MOVE_DATA:
		{
			Message::ControlInfo* mci = (Message::ControlInfo*) mp;
			//new MessageMoveRequest(this->id , )
			switch (mci->glutKey)
			{
				case GLUT_KEY_LEFT:
					lastDirection = Direction::LEFT;
					break;

				case GLUT_KEY_UP:
					if (this->_boostTimer == 0)
					{
						switch (this->availableBoostType)
						{
							case Message::BOOST_SPEED:
								this->jumpInterval /= 2;
								_boostTimer = 5000;
								break;

							case Message::BOOST_JUMP:
								this->_boostTimer = 700;
								break;

							default:
								break;
						}
					}

					break;

				case GLUT_KEY_RIGHT:
					lastDirection = Direction::RIGHT;
					break;
					/*
					 case GLUT_KEY_DOWN:
					 break;
					 */
				default:
					break;
			}

		}
			break;

		case Message::ADD_BRICK:

			if (availableBoostType != Message::BOOST_JUMP)
			{
				if (((Message::AddBrick*) mp)->newHead.position.z > 0)
				{
					--((Message::AddBrick*) mp)->newHead.position.z;
				}
			}
			else
			{
				if (this->_boostTimer > 0)
				{
					++((Message::AddBrick*) mp)->newHead.position.z;
					_boostTimer = 1;
					availableBoostType = 0;
				}
			}

			this->tail.push_back(((Message::AddBrick*) mp)->newHead);
			if (this->tail.size() > tailMaxLenght)
				this->tail.pop_front();
			break;

		case Message::REQUEST_DIRECTION:
			this->lastDirection = ((Message::ChangeMoveDirectionRequest*) mp)->direction;
			break;
		case Message::SET_REAL_POSITION:
		{
			this->headRealPos = ((Message::SetRealPosition*) mp)->realPosition;

			if (!(lastReadlPosition == headRealPos))
			{
				lastReadlPosition = headRealPos;
			}
		}
			break;

		case Message::COLLISION_NOTIFICATION:
		{
			((Message::CollisionNotification*) (mp))->otherObject->giveMessage(new Message::SimpleNotification(this->ID, Message::KILL));
		}
			break;

		case Message::BOOST_ADD:
		{
			Message::AddBoost* ab = (Message::AddBoost*) mp;

			parent->giveMessage(new Message::AddPoints(this->ID, Message::PLAYER_1, ab->value));

			switch (ab->boostType)
			{
				case Message::CHANGE_LENGHT:
					this->tailMaxLenght += ab->value;
					break;
				case Message::BOOST_SPEED:
					if (this->availableBoostType == 0)
					{
						this->availableBoostType = Message::BOOST_SPEED;
						this->parent->giveMessage(new Message::SimpleNotification(this->ID, Message::BOOST_OBTAINED_SPEED));
					}
					break;
				case Message::BOOST_JUMP:
					if (this->availableBoostType == 0)
					{
						this->availableBoostType = Message::BOOST_JUMP;
						this->parent->giveMessage(new Message::SimpleNotification(this->ID, Message::BOOST_OBTAINED_JUMP));
					}
					break;

				default:
					break;
			};
		}
			break;

		case Message::SIMPLE_NOTIFICATION:
		{
			if (((Message::SimpleNotification*) mp)->notification == Message::KILL)
				this->parent->giveMessage(new Message::SimpleNotification(this->ID, Message::PLAYER_1_DEAD));
		}
			break;

		default:
			break;
	}

	delete mp;
}

void SnakeBody::update(int mili)
{
	innerTimer1 += mili;
	totalMiliseconds += mili;

	this->position = (*(--this->tail.end())).position;

	//BOOST HANDLING
	if (this->_boostTimer > 0)
	{
		_boostTimer -= mili;

		if (_boostTimer <= 0)
		{
			//end of boost
			_boostTimer = 0;

			this->parent->giveMessage(new Message::SimpleNotification(this->ID, Message::BOOST_USED)); //sending notification to snakeAbilitiesIndicator

			switch (this->availableBoostType)
			{
				case Message::BOOST_SPEED:
					this->jumpInterval *= 2;
					break;

				case Message::BOOST_JUMP:
					//nothing to do here
					break;

				default:
					break;
			}
			this->availableBoostType = 0;
		}
	}

	//MOVE
	if (innerTimer1 > jumpInterval)
	{
		innerTimer1 -= jumpInterval;
		this->parent->giveMessage(new Message::MoveRequest(this->ID, (*(--this->tail.end())), lastDirection));
		lastDirection = Direction::UP;
	}

	parent->giveMessage(new Message::GetRealPosition(this->ID, (--tail.end())->position));
}

void SnakeBody::init()
{

}
