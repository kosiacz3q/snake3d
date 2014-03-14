/*
 * MapObject.h
 *
 *  Created on: Aug 27, 2013
 *      Author: lucas
 */

#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_


#include <list>

#include "Object.h"
#include "BrickProperties.h"
#include "IMessager.h"

typedef std::list<BrickProperties> Tail;

class MapObject: public Object , public IMessager {
public:
	MapObject(object_type type);

	bool hitable;
	Tail tail;
	IMessager* parent;
};

#endif /* MAPOBJECT_H_ */
