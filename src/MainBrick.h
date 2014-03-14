/*
 * MainBrick.h
 *
 *  Created on: Aug 25, 2013
 *      Author: lucas
 */

#ifndef MAINBRICK_H_
#define MAINBRICK_H_

#include <map>
#include <vector>

#include "Brick.h"
#include "SnakeBody.h"
#include "Obstacle.h"
#include "Gainer.h"


typedef std::map<int,MapObject*> MapObjects;
typedef std::vector<Message::MessagePack*> MessagesVector;

class MainBrick : public IMessager{
public:
	MainBrick();
	virtual ~MainBrick();

	void drawAll();
	void updateAll(int time);

	void addMapObject(MapObject* obj);
	void removeMapObject(int id);

	//@override
	void giveMessage(Message::MessagePack*);

	void setParent(IMessager* parent){
		this->parent = parent;
	}

	float halfOfMainBrick;
	float halfOfObjectsBrick;
	float objectsBrickDimm;
	Brick* mainBrick;
	Brick* objectsBrick;
	int** wallDim;
	Message::ControlInfo* controlInfo;
	int snakeID;

private:
	MapObjects objects;
	MessagesVector messages;
	IMessager* parent;
	int translationTab[5];

	void detectCollisions();
	/*****DIRECTION TRANSLATION HANDLERS**********/
	void clockwiseTranslate();
	void counterclockwiseTranslate();

};

#endif /* MAINBRICK_H_ */
