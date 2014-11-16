#include <math.h>

#include "ShapeGenerator.h"
#include "Camera.h"
#include "gamestage/GameStateManager.h"
#include "MainBrickHandler.h"
#include "RandomPositionGenerator.h"

MainBrickHandler::~MainBrickHandler()
{
	delete mainBrick;
	delete objectsBrick;
	delete wallDim;
	delete controlInfo;
	controlInfo = 0;
}

MainBrickHandler::MainBrickHandler()
{
	mainBrick = new Brick();
	objectsBrick = new Brick();

	wallDim = NULL;
	messages = MessagesVector();
	controlInfo = new Message::ControlInfo(0);
	snakeID = 0;
	parent = 0;
	objects = MapObjects();

	translationTab[Direction::DOWN] = Direction::DOWN;
	translationTab[Direction::UP] = Direction::UP;
	translationTab[Direction::LEFT] = Direction::LEFT;
	translationTab[Direction::RIGHT] = Direction::RIGHT;
	translationTab[Direction::NONE] = Direction::NONE;
}

void MainBrickHandler::drawAll()
{
	mainBrick->draw();

	glPushMatrix();

	glTranslatef(mainBrick->getPosition().x, mainBrick->getPosition().y, mainBrick->getPosition().z);
	glRotatef(mainBrick->getRotation().x, 0., 1., 0.);
	glRotatef(mainBrick->getRotation().y, 1., 0., 0.);
	glRotatef(mainBrick->getRotation().z, 0., 0., 1.);

	for (MapObjects::const_iterator obj_iter = objects.begin(); obj_iter != objects.end(); ++obj_iter)
	{
		for (Tail::const_iterator tail_iter = obj_iter->second->getTail().begin(); tail_iter != obj_iter->second->getTail().end(); ++tail_iter)
		{
			objectsBrick->setColor(tail_iter->color);

			glPushMatrix();

			switch ((int) tail_iter->position.w)
			{
				case 1:
					glTranslatef((tail_iter->position.x - wallDim[0][2]) * objectsBrick->getEdgeLength(), (wallDim[0][3] - tail_iter->position.y) * objectsBrick->getEdgeLength(),
									(mainBrick->getEdgeLength() / 2) + (objectsBrick->getEdgeLength() / 2) + (tail_iter->position.z * objectsBrick->getEdgeLength()));
					break;
				case 2:
					glTranslatef((mainBrick->getEdgeLength() / 2) + (objectsBrick->getEdgeLength() / 2) + (tail_iter->position.z * objectsBrick->getEdgeLength()),
									(wallDim[1][3] - tail_iter->position.y) * objectsBrick->getEdgeLength(), (tail_iter->position.x - wallDim[1][2]) * objectsBrick->getEdgeLength());
					break;
				case 3:
					glTranslatef((tail_iter->position.x - wallDim[2][2]) * objectsBrick->getEdgeLength(), (wallDim[2][3] - tail_iter->position.y) * objectsBrick->getEdgeLength(),
									-(mainBrick->getEdgeLength() / 2) - (objectsBrick->getEdgeLength() / 2) - (tail_iter->position.z * objectsBrick->getEdgeLength()));
					break;

				case 4:
					glTranslatef(-(mainBrick->getEdgeLength() / 2) - (objectsBrick->getEdgeLength() / 2) - (tail_iter->position.z * objectsBrick->getEdgeLength()),
									(wallDim[3][3] - tail_iter->position.y) * objectsBrick->getEdgeLength(), (tail_iter->position.x - wallDim[3][2]) * objectsBrick->getEdgeLength());
					break;

				case 5:
					glTranslatef((tail_iter->position.x - wallDim[4][2]) * objectsBrick->getEdgeLength(),
									-(mainBrick->getEdgeLength() / 2) - (objectsBrick->getEdgeLength() / 2) - (tail_iter->position.z * objectsBrick->getEdgeLength()),
									(wallDim[4][3] - tail_iter->position.y) * objectsBrick->getEdgeLength());
					break;

				case 6:
					glTranslatef((tail_iter->position.x - wallDim[5][2]) * objectsBrick->getEdgeLength(),
									(mainBrick->getEdgeLength() / 2) + (objectsBrick->getEdgeLength() / 2) + (tail_iter->position.z * objectsBrick->getEdgeLength()),
									(wallDim[5][3] - tail_iter->position.y) * objectsBrick->getEdgeLength());
					break;
				default:
					break;
			}

			objectsBrick->draw();
			glPopMatrix();
		}
	}

	glPopMatrix();
}

void MainBrickHandler::addMapObject(MapObject* obj)
{
	objects.insert(std::make_pair(obj->getID(), obj));
	RandomPositionGenerator::addReservedPosition(obj->getTail().begin()->position);
	obj->setParent(this);
}

void MainBrickHandler::giveMessage(Message::MessagePack* mp)
{
	messages.push_back(mp);
}

void MainBrickHandler::updateAll(int time)
{
	for (MapObjects::const_iterator iter = objects.begin(); iter != objects.end(); ++iter)
	{
		iter->second->update(time);
	}

	MainBrickHandler::detectCollisions();

	for (MessagesVector::iterator iter = messages.begin();
			iter != messages.end() && GameStateManager::getActualGameStage()->getGameStageEnum() == GAME_STAGE::GAME; ++iter)
	{
		switch ((*iter)->msgType)
		{
			case Message::MOVE_REQUEST:
			{
				Message::MoveRequest* mvr = (Message::MoveRequest*) (*iter);

				/**********TRANSLATION***********/
				int originalDirection = mvr->direction;
				mvr->direction = translationTab[mvr->direction];

				switch ((int) mvr->head.position.w)
				{
					/****************FIRST WALL*******************/
					case 1:
					{
						/*******CALCULATING NEW POSITION**********/
						switch (mvr->direction)
						{
							case Direction::DOWN:
								mvr->head.position.y += 1;
								break;
							case Direction::UP:
								mvr->head.position.y -= 1;
								break;
							case Direction::RIGHT:
								mvr->head.position.x += 1;
								break;
							case Direction::LEFT:
								mvr->head.position.x -= 1;
								break;
							default:
								break;
						}

						/*************WALL JUMPING***************/
						if (mvr->head.position.x > 22)
						{
							//jump to second wall
							mvr->head.position.w = 2;
							mvr->head.position.x = 20;
						}
						else if (mvr->head.position.x < 0)
						{
							//jump to fourth wall
							mvr->head.position.w = 4;
							mvr->head.position.x = 20;
						}
						else if (mvr->head.position.y < 0)
						{
							if (mvr->head.position.x == 0)
							{
								//jump to fourth wall
								mvr->head.position.w = 4;
								mvr->head.position.y = 0;
								mvr->head.position.x = 20;
								counterclockwiseTranslate();
							}
							else if (mvr->head.position.x == 22)
							{
								//jump to second wall
								mvr->head.position.w = 2;
								mvr->head.position.y = 0;
								mvr->head.position.x = 20;
								clockwiseTranslate();
							}
							else
							{
								//jump to sixth wall
								mvr->head.position.w = 6;
								--mvr->head.position.x;
								++mvr->head.position.y;
							}
						}
						else if (mvr->head.position.y > 22)
						{
							if (mvr->head.position.x == 0)
							{
								//jump to fourth wall
								mvr->head.position.w = 4;
								mvr->head.position.x = 20;
								mvr->head.position.y = 22;
								counterclockwiseTranslate();
							}
							else if (mvr->head.position.x == 22)
							{
								//jump to second wall
								mvr->head.position.w = 2;
								mvr->head.position.x = 20;
								mvr->head.position.y = 22;
								clockwiseTranslate();
							}
							else
							{
								// jump to fifth wall
								mvr->head.position.w = 5;
								mvr->head.position.y = 0;
								--mvr->head.position.x;
							}
						}
					}
						break;
						/******************SECOND WALL*****************/
					case 2:
					{
						switch (mvr->direction)
						{
							case Direction::DOWN:
								mvr->head.position.y += 1;
								break;
							case Direction::UP:
								mvr->head.position.y -= 1;
								break;
							case Direction::RIGHT:
								mvr->head.position.x -= 1;
								break;
							case Direction::LEFT:
								mvr->head.position.x += 1;
								break;
							default:
								break;
						}

						/*************WALL JUMPING***************/
						if (mvr->head.position.x > 20)
						{
							//jump to first wall
							mvr->head.position.w = 1;
							mvr->head.position.x = 22;
						}
						else if (mvr->head.position.x < 0)
						{
							//jump to third wall
							mvr->head.position.w = 3;
							mvr->head.position.x = 22;

						}
						else if (mvr->head.position.y > 22)
						{
							//jump to fifth wall
							mvr->head.position.w = 5;
							counterclockwiseTranslate();
							mvr->head.position.y = 20 - mvr->head.position.x;
							mvr->head.position.x = 20;
						}
						else if (mvr->head.position.y < 0)
						{
							//jump to sixth wall
							mvr->head.position.w = 6;
							clockwiseTranslate();
							mvr->head.position.y = 20 - mvr->head.position.x;
							mvr->head.position.x = 20;
						}

					}
						break;
						/**************THIRD WALL********************/
					case 3:
					{
						switch (mvr->direction)
						{
							case Direction::DOWN:
								mvr->head.position.y += 1;
								break;
							case Direction::UP:
								mvr->head.position.y -= 1;
								break;
							case Direction::RIGHT:
								mvr->head.position.x -= 1;
								break;
							case Direction::LEFT:
								mvr->head.position.x += 1;
								break;
							default:
								break;
						}
						/**************JUMPS*****************/
						if (mvr->head.position.x > 22)
						{
							//jump to second wall
							mvr->head.position.w = 2;
							mvr->head.position.x = 0;
						}
						else if (mvr->head.position.x < 0)
						{
							//jump to fourth wall
							mvr->head.position.w = 4;
							mvr->head.position.x = 0;
						}
						else if (mvr->head.position.y < 0)
						{
							if (mvr->head.position.x == 0)
							{
								//jump to fourth wall
								mvr->head.position.w = 4;
								mvr->head.position.y = 0;
								mvr->head.position.x = 0;
								clockwiseTranslate();
							}
							else if (mvr->head.position.x == 22)
							{
								//jump to second wall
								mvr->head.position.w = 2;
								mvr->head.position.y = 0;
								mvr->head.position.x = 0;
								counterclockwiseTranslate();
							}
							else
							{
								//jump to sixth wall
								mvr->head.position.w = 6;
								--mvr->head.position.x;
								mvr->head.position.y = 20;
								clockwiseTranslate();
								clockwiseTranslate();
							}
						}
						else if (mvr->head.position.y > 22)
						{
							if (mvr->head.position.x == 0)
							{
								//jump to fourth wall
								mvr->head.position.w = 4;
								mvr->head.position.x = 0;
								mvr->head.position.y = 22;
								clockwiseTranslate();
							}
							else if (mvr->head.position.x == 22)
							{
								//jump to second wall
								mvr->head.position.w = 2;
								mvr->head.position.x = 0;
								mvr->head.position.y = 22;
								counterclockwiseTranslate();
							}
							else
							{
								// jump to fifth wall
								mvr->head.position.w = 5;
								mvr->head.position.y = 20;
								clockwiseTranslate();
								clockwiseTranslate();
								--mvr->head.position.x;
							}
						}

					}
						break;
						/**************FOURTH WALL*******************/
					case 4:
					{
						switch (mvr->direction)
						{
							case Direction::DOWN:
								mvr->head.position.y += 1;
								break;
							case Direction::UP:
								mvr->head.position.y -= 1;
								break;
							case Direction::RIGHT:
								mvr->head.position.x += 1;
								break;
							case Direction::LEFT:
								mvr->head.position.x -= 1;
								break;
							default:
								break;
						}

						/*************WALL JUMPING***************/
						if (mvr->head.position.x > 20)
						{
							//jump to first wall
							mvr->head.position.w = 1;
							mvr->head.position.x = 0;
						}
						else if (mvr->head.position.x < 0)
						{
							// jump to third wall
							mvr->head.position.w = 3;
							mvr->head.position.x = 0;
						}
						else if (mvr->head.position.y < 0)
						{
							////jump to sixth wall
							mvr->head.position.w = 6;
							counterclockwiseTranslate();
							mvr->head.position.y = 20 - mvr->head.position.x;
							mvr->head.position.x = 0;
						}
						else if (mvr->head.position.y > 22)
						{
							//jump to fifth wall
							mvr->head.position.w = 5;
							clockwiseTranslate();
							mvr->head.position.y = 20 - mvr->head.position.x;
							mvr->head.position.x = 0;
						}
					}
						break;
						/***************FIFTH WALL*******************/
					case 5:
					{
						switch (mvr->direction)
						{
							case Direction::DOWN:
								mvr->head.position.y += 1;
								break;
							case Direction::UP:
								mvr->head.position.y -= 1;
								break;
							case Direction::RIGHT:
								mvr->head.position.x += 1;
								break;
							case Direction::LEFT:
								mvr->head.position.x -= 1;
								break;
							default:
								break;
						}

						/*************WALL JUMPING***************/
						if (mvr->head.position.x > 20)
						{
							//jump to second wall
							mvr->head.position.w = 2;
							clockwiseTranslate();
							mvr->head.position.x = 20 - mvr->head.position.y;
							mvr->head.position.y = 22;

						}
						else if (mvr->head.position.x < 0)
						{
							//jump to fourth wall
							mvr->head.position.w = 4;
							counterclockwiseTranslate();
							mvr->head.position.x = 20 - mvr->head.position.y;
							mvr->head.position.y = 22;
						}
						else if (mvr->head.position.y > 20)
						{
							//jump to third wall
							counterclockwiseTranslate();
							counterclockwiseTranslate();
							mvr->head.position.w = 3;
							++mvr->head.position.x;
							mvr->head.position.y = 22;
						}
						else if (mvr->head.position.y < 0)
						{
							//jump to first wall
							mvr->head.position.w = 1;
							++mvr->head.position.x;
							mvr->head.position.y = 22;
						}
					}
						break;
						/***************SIXTH WALL*******************/
					case 6:
					{
						switch (mvr->direction)
						{
							case Direction::DOWN:
								mvr->head.position.y -= 1;
								break;
							case Direction::UP:
								mvr->head.position.y += 1;
								break;
							case Direction::RIGHT:
								mvr->head.position.x += 1;
								break;
							case Direction::LEFT:
								mvr->head.position.x -= 1;
								break;
							default:
								break;
						}

						if (mvr->head.position.x > 20)
						{
							//jump to second wall
							mvr->head.position.w = 2;
							mvr->head.position.x = 20 - mvr->head.position.y;
							mvr->head.position.y = 0;
							counterclockwiseTranslate();

						}
						else if (mvr->head.position.x < 0)
						{
							//jump to fourth wall
							mvr->head.position.w = 4;
							clockwiseTranslate();
							//crossInverseTranslationTab();
							mvr->head.position.x = 20 - mvr->head.position.y;
							mvr->head.position.y = 0;
						}
						else if (mvr->head.position.y > 20)
						{
							//jump to third wall
							clockwiseTranslate();
							clockwiseTranslate();
							mvr->head.position.w = 3;
							++mvr->head.position.x;
							mvr->head.position.y = 0;
						}
						else if (mvr->head.position.y < 0)
						{
							//jump to first wall
							mvr->head.position.w = 1;
							++mvr->head.position.x;
							mvr->head.position.y = 0;
						}
					}
						break;

					default:
						break;
				}

				/********POST MOVE TRANSLATION********/
				if (originalDirection == Direction::LEFT)
				{
					clockwiseTranslate();
				}
				else if (originalDirection == Direction::RIGHT)
				{
					counterclockwiseTranslate();
				}

				//setting color
				if (GameStateManager::getProperty(Properties::COLOR_PER_WALL).compare("yes") == 0)
				{
					switch ((int) mvr->head.position.w)
					{
						case 1:
							mvr->head.color = Colors::Blue;
							break;
						case 2:
							mvr->head.color = Colors::Crimson;
							break;
						case 3:
							mvr->head.color = Colors::Cyan;
							break;
						case 4:
							mvr->head.color = Colors::Orange;
							break;
						case 5:
							mvr->head.color = Colors::LimeGreen;
							break;
						case 6:
							mvr->head.color = Colors::DarkViolet;
							break;
					}
				}

				/*******SENDING MESSAGE************/
				objects[mvr->senderID]->giveMessage(new Message::AddBrick(0, BrickProperties(mvr->head.position, mvr->head.color)));

			}
				break;

			case Message::REQUEST_REAL_POSITION:
			{
				Message::GetRealPosition* mgrp = (Message::GetRealPosition*) (*iter);

				Vector3f realPos = Vector3f();

				switch ((int) mgrp->head.w)
				{
					case 1:
					{
						realPos.z = (mainBrick->getEdgeLength() / 2) - (objectsBrick->getEdgeLength() / 2);
						realPos.x = (mgrp->head.x * objectsBrick->getEdgeLength()) - (mainBrick->getEdgeLength() / 2) - (objectsBrick->getEdgeLength() / 2);
						realPos.y = (mainBrick->getEdgeLength() / 2) - (mgrp->head.y * objectsBrick->getEdgeLength());
					}
						break;
					case 2:
					{ //CONFIRMED
						realPos.x = (mainBrick->getEdgeLength() / 2) + (objectsBrick->getEdgeLength() / 2);
						realPos.y = (mainBrick->getEdgeLength() / 2) - (mgrp->head.y * objectsBrick->getEdgeLength());
						realPos.z = (mgrp->head.x * objectsBrick->getEdgeLength()) - (mainBrick->getEdgeLength() / 2);
					}
						break;
					case 3:
					{
						realPos.z = -(mainBrick->getEdgeLength() / 2);
						realPos.x = (mgrp->head.x * objectsBrick->getEdgeLength()) - (mainBrick->getEdgeLength() / 2) - (objectsBrick->getEdgeLength() / 2);
						realPos.y = (mainBrick->getEdgeLength() / 2) - (mgrp->head.y * objectsBrick->getEdgeLength());
					}
						break;
					case 4:
					{ //CONFIRMED
						realPos.x = -(mainBrick->getEdgeLength() / 2) - (objectsBrick->getEdgeLength() / 2);
						realPos.y = (mainBrick->getEdgeLength() / 2) - (mgrp->head.y * objectsBrick->getEdgeLength());
						realPos.z = (mgrp->head.x * objectsBrick->getEdgeLength()) - (mainBrick->getEdgeLength() / 2);
					}
						break;

					case 5:
					{ //CONFIRMED
						realPos.y = -(mainBrick->getEdgeLength() / 2) - objectsBrick->getEdgeLength();
						realPos.x = -(mainBrick->getEdgeLength() / 2) + (mgrp->head.x * objectsBrick->getEdgeLength()) + (objectsBrick->getEdgeLength() / 2);
						realPos.z = (mainBrick->getEdgeLength() / 2) - (mgrp->head.y * objectsBrick->getEdgeLength()) - objectsBrick->getEdgeLength();
					}
						break;
					case 6:
					{ //CONFIRMED
						realPos.y = (mainBrick->getEdgeLength() / 2);
						realPos.x = (mgrp->head.x * objectsBrick->getEdgeLength()) - (mainBrick->getEdgeLength() / 2) + (objectsBrick->getEdgeLength() / 2);
						realPos.z = (mainBrick->getEdgeLength() / 2) - (mgrp->head.y * objectsBrick->getEdgeLength()) - objectsBrick->getEdgeLength();
					}
						break;
					default:
						break;
				}
				objects[mgrp->senderID]->giveMessage(new Message::SetRealPosition(0, realPos));

			}
				break;

			case Message::SIMPLE_NOTIFICATION:
			{
				switch (((Message::SimpleNotification*) *iter)->notification)
				{
					case Message::DISPOSE_ME_REQUEST:
						MainBrickHandler::removeMapObject((*iter)->senderID);

						break;

					case Message::PLAYER_1_DEAD:
						GameStateManager::setProperty(Properties::NEW_HIGHSCORE_INDICATOR, "true");
						delete *iter;
						GameStateManager::startDeathScreenState();
						return;
						break;

					case Message::BOOST_OBTAINED_JUMP:
					case Message::BOOST_OBTAINED_SPEED:
					case Message::BOOST_USED:
						this->parent->giveMessage(*iter);
					default:
						break;
				}
			}
				break;

			case Message::ADD_POINTS:

				this->parent->giveMessage(*iter);
				break;

			default:
				break;
		}

		delete *iter;
	}

	messages.clear();

	if (controlInfo != 0)
	{
		//sending input to player snake
		Message::ControlInfo* cif = new Message::ControlInfo(0);
		cif->key = controlInfo->key;
		cif->glutKey = controlInfo->glutKey;
		objects[snakeID]->giveMessage(cif);
		controlInfo->reset();
		Camera::updatePosition(((SnakeBody*) (objects[snakeID]))->getHeadRealPosition());
	}
}

void MainBrickHandler::detectCollisions()
{
	Vector4f snakeHeadPosition = (--objects.at(snakeID)->getTail().end())->position;

	//collision with obstacles
	for (MapObjects::const_iterator obj_iter = objects.begin(); obj_iter != objects.end(); ++obj_iter)
	{
		if (obj_iter->first != snakeID && obj_iter->second->isHitable())
		{
			for (Tail::iterator tailIter = obj_iter->second->getTail().begin(); tailIter != obj_iter->second->getTail().end(); ++tailIter)
				if (tailIter->position == snakeHeadPosition)
				{
					objects.at(snakeID)->giveMessage(new Message::CollisionNotification(0, (IMessager*) ((obj_iter->second))));
					obj_iter->second->giveMessage(new Message::CollisionNotification(0, (IMessager*) (objects.at(snakeID))));
				}
		}
	}

	//collision with ourself

	if (objects.at(snakeID)->getTail().size() > 3)
	{
		auto headSegment = (--objects.at(snakeID)->getTail().end());
		for (auto snakeSegment = objects.at(snakeID)->getTail().begin(); snakeSegment != headSegment; ++snakeSegment)
		{
			if (snakeSegment->position == snakeHeadPosition)
			{
				GameStateManager::setProperty(Properties::DEATH_CAUSE, "You ate yourself...");
				objects.at(snakeID)->giveMessage(new Message::SimpleNotification(0, Message::KILL));
			}
		}
	}

}

void MainBrickHandler::clockwiseTranslate()
{
	int tmp = translationTab[4];
	translationTab[4] = translationTab[3];
	translationTab[3] = translationTab[2];
	translationTab[2] = translationTab[1];
	translationTab[1] = tmp;
}

void MainBrickHandler::counterclockwiseTranslate()
{
	int tmp = translationTab[1];
	translationTab[1] = translationTab[2];
	translationTab[2] = translationTab[3];
	translationTab[3] = translationTab[4];
	translationTab[4] = tmp;
}

void MainBrickHandler::removeMapObject(int id)
{
	MapObject* obj = objects[id];

	RandomPositionGenerator::removeReservedPosition(obj->getTail().begin()->position);
	objects.erase(id);
	delete obj;

}

void MainBrickHandler::init()
{
	mainBrick->setEdgeLength(2.1f);
	objectsBrick->setEdgeLength(0.1f);

	mainBrick->init();
	objectsBrick->init();

	mainBrick->setPosition(Vector3f(0., 0., 0.));

	mainBrick->goLsdGo();

	wallDim = new int*[6];
	for (int i = 0; i < 6; ++i)
		wallDim[i] = new int[4]; //width height centerX  centerY

	wallDim[0][0] = 23; //x max
	wallDim[0][1] = 23; //y max
	wallDim[0][2] = 12 - 1; // x center
	wallDim[0][3] = 12 - 1; // y center

	wallDim[1][0] = 21;
	wallDim[1][1] = 23;
	wallDim[1][2] = 11 - 1;
	wallDim[1][3] = 12 - 1;

	wallDim[2][0] = 23;
	wallDim[2][1] = 23;
	wallDim[2][2] = 12 - 1;
	wallDim[2][3] = 12 - 1;

	wallDim[3][0] = 21;
	wallDim[3][1] = 23;
	wallDim[3][2] = 11 - 1;
	wallDim[3][3] = 12 - 1;

	wallDim[4][0] = 21;
	wallDim[4][1] = 21;
	wallDim[4][2] = 11 - 1;
	wallDim[4][3] = 11 - 1;

	wallDim[5][0] = 21;
	wallDim[5][1] = 21;
	wallDim[5][2] = 11 - 1;
	wallDim[5][3] = 11 - 1;
}

void MainBrickHandler::setSnakeId(long int id)
{
	snakeID = id;
}

void MainBrickHandler::addObstacle(int count)
{
	for (int i = 0; i < count; ++i)
	{
		Obstacle* obstacle = new Obstacle();
		obstacle->getTail().push_back(BrickProperties(RandomPositionGenerator::generate(wallDim, -1, 5, 20, i * 5), Colors::Black));
		addMapObject(obstacle);
	}
}

void MainBrickHandler::addGainers(Message::BoostType type, int count)
{
	const float* color;
	int power = 20;
	switch (type)
	{
		case Message::BOOST_SPEED:
			color = Colors::Red;
			break;
		case Message::BOOST_JUMP:
			color = Colors::Yellow;
			break;
		case Message::CHANGE_LENGHT:
			color = Colors::Gray;
			power = 1;
			break;
		default:
			color = Colors::Gray;
	}

	MapObject* gainer = nullptr;

	for (int i = 0; i < count; ++i)
	{
		gainer = new Gainer(type, power);
		gainer->getTail().push_back(BrickProperties(RandomPositionGenerator::generate(wallDim, -1, 5, 20, i * 20), color));
	}

	addMapObject(gainer);
}
