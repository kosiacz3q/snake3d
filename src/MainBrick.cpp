#include "MainBrick.h"
#include "ShapeGenerator.h"
#include <math.h>
#include "Camera.h"
#include "gamestage/GameStateManager.h"
#include "RandomPositionGenerator.h"

MainBrick::~MainBrick()
{
	delete mainBrick;
	delete objectsBrick;
	delete wallDim;
	delete controlInfo;
	controlInfo = 0;
}

MainBrick::MainBrick()
{
	mainBrick = new Brick();
	objectsBrick = new Brick();
	halfOfMainBrick = 0;
	halfOfObjectsBrick = 0;
	objectsBrickDimm = (float) NULL;
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

void MainBrick::drawAll()
{
	mainBrick->draw();

	glPushMatrix();

	glTranslatef(this->mainBrick->position.x, this->mainBrick->position.y, this->mainBrick->position.z);
	glRotatef(this->mainBrick->rotation.x, 0., 1., 0.);
	glRotatef(this->mainBrick->rotation.y, 1., 0., 0.);
	glRotatef(this->mainBrick->rotation.z, 0., 0., 1.);

	for (MapObjects::const_iterator obj_iter = objects.begin(); obj_iter != objects.end(); ++obj_iter)
	{
		for (Tail::const_iterator tail_iter = obj_iter->second->tail.begin(); tail_iter != obj_iter->second->tail.end(); ++tail_iter)
		{
			ShapeGenerator::setColorOnSquare(objectsBrick->color_normal_vertex, 8, tail_iter->color);
			glPushMatrix();

			switch ((int) tail_iter->position.w)
			{
				case 1:
					glTranslatef((tail_iter->position.x - wallDim[0][2]) * objectsBrickDimm, (wallDim[0][3] - tail_iter->position.y) * objectsBrickDimm,
									halfOfMainBrick + halfOfObjectsBrick + (tail_iter->position.z * objectsBrickDimm));
					break;
				case 2:
					glTranslatef(halfOfMainBrick + halfOfObjectsBrick + (tail_iter->position.z * objectsBrickDimm),
									(wallDim[1][3] - tail_iter->position.y) * objectsBrickDimm, (tail_iter->position.x - wallDim[1][2]) * objectsBrickDimm);
					break;
				case 3:
					glTranslatef((tail_iter->position.x - wallDim[2][2]) * objectsBrickDimm, (wallDim[2][3] - tail_iter->position.y) * objectsBrickDimm,
									-halfOfMainBrick - halfOfObjectsBrick - (tail_iter->position.z * objectsBrickDimm));
					break;

				case 4:
					glTranslatef(-halfOfMainBrick - halfOfObjectsBrick - (tail_iter->position.z * objectsBrickDimm),
									(wallDim[3][3] - tail_iter->position.y) * objectsBrickDimm, (tail_iter->position.x - wallDim[3][2]) * objectsBrickDimm);
					break;

				case 5:
					glTranslatef((tail_iter->position.x - wallDim[4][2]) * objectsBrickDimm,
									-halfOfMainBrick - halfOfObjectsBrick - (tail_iter->position.z * objectsBrickDimm),
									(wallDim[4][3] - tail_iter->position.y) * objectsBrickDimm);
					break;

				case 6:
					glTranslatef((tail_iter->position.x - wallDim[5][2]) * objectsBrickDimm,
									halfOfMainBrick + halfOfObjectsBrick + (tail_iter->position.z * objectsBrickDimm),
									(wallDim[5][3] - tail_iter->position.y) * objectsBrickDimm);
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

void MainBrick::addMapObject(MapObject* obj)
{
	objects.insert(std::make_pair(obj->getID(), obj));
	RandomPositionGenerator::addReservedPosition(obj->tail.begin()->position);
	obj->parent = this;
}

void MainBrick::giveMessage(Message::MessagePack* mp)
{
	messages.push_back(mp);
}

void MainBrick::updateAll(int time)
{
	for (MapObjects::const_iterator iter = objects.begin(); iter != objects.end(); ++iter)
	{
		iter->second->update(time);
	}

	MainBrick::detectCollisions();

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
						realPos.z = halfOfMainBrick - halfOfObjectsBrick;
						realPos.x = (mgrp->head.x * objectsBrickDimm) - halfOfMainBrick - halfOfObjectsBrick;
						realPos.y = halfOfMainBrick - (mgrp->head.y * objectsBrickDimm);
					}
						break;
					case 2:
					{ //CONFIRMED
						realPos.x = halfOfMainBrick + halfOfObjectsBrick;
						realPos.y = halfOfMainBrick - (mgrp->head.y * objectsBrickDimm);
						realPos.z = (mgrp->head.x * objectsBrickDimm) - halfOfMainBrick;
					}
						break;
					case 3:
					{
						realPos.z = -halfOfMainBrick;
						realPos.x = (mgrp->head.x * objectsBrickDimm) - halfOfMainBrick - halfOfObjectsBrick;
						realPos.y = halfOfMainBrick - (mgrp->head.y * objectsBrickDimm);
					}
						break;
					case 4:
					{ //CONFIRMED
						realPos.x = -halfOfMainBrick - halfOfObjectsBrick;
						realPos.y = halfOfMainBrick - (mgrp->head.y * objectsBrickDimm);
						realPos.z = (mgrp->head.x * objectsBrickDimm) - halfOfMainBrick;
					}
						break;

					case 5:
					{ //CONFIRMED
						realPos.y = -halfOfMainBrick - objectsBrickDimm;
						realPos.x = -halfOfMainBrick + (mgrp->head.x * objectsBrickDimm) + halfOfObjectsBrick;
						realPos.z = halfOfMainBrick - (mgrp->head.y * objectsBrickDimm) - objectsBrickDimm;
					}
						break;
					case 6:
					{ //CONFIRMED
						realPos.y = halfOfMainBrick;
						realPos.x = (mgrp->head.x * objectsBrickDimm) - halfOfMainBrick + halfOfObjectsBrick;
						realPos.z = halfOfMainBrick - (mgrp->head.y * objectsBrickDimm) - objectsBrickDimm;
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
						MainBrick::removeMapObject((*iter)->senderID);

						break;

					case Message::PLAYER_1_DEAD:
						GameStateManager::setProperty(Properties::NEW_HIGHSCORE_INDICATOR, "true");
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
		Camera::updatePosition(((SnakeBody*) (objects[snakeID]))->headRealPos);
	}
}

void MainBrick::detectCollisions()
{
	Vector4f snakeHeadPosition = (--objects.at(snakeID)->tail.end())->position;
	for (MapObjects::const_iterator obj_iter = objects.begin(); obj_iter != objects.end(); ++obj_iter)
	{
		if (obj_iter->first != snakeID && obj_iter->second->hitable)
		{
			for (Tail::iterator tailIter = obj_iter->second->tail.begin(); tailIter != obj_iter->second->tail.end(); ++tailIter)
				if (tailIter->position == snakeHeadPosition)
				{
					objects.at(snakeID)->giveMessage(new Message::CollisionNotification(0, (IMessager*) ((obj_iter->second))));
					obj_iter->second->giveMessage(new Message::CollisionNotification(0, (IMessager*) (objects.at(snakeID))));
				}
		}
	}
}

void MainBrick::clockwiseTranslate()
{
	int tmp = translationTab[4];
	translationTab[4] = translationTab[3];
	translationTab[3] = translationTab[2];
	translationTab[2] = translationTab[1];
	translationTab[1] = tmp;
}

void MainBrick::counterclockwiseTranslate()
{
	int tmp = translationTab[1];
	translationTab[1] = translationTab[2];
	translationTab[2] = translationTab[3];
	translationTab[3] = translationTab[4];
	translationTab[4] = tmp;
}

void MainBrick::removeMapObject(int id)
{
	MapObject* obj = objects[id];

	RandomPositionGenerator::removeReservedPosition(obj->tail.begin()->position);
	objects.erase(id);
	delete obj;

}
