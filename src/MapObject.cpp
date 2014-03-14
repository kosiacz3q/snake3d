/*
 * MapObject.cpp
 *
 *  Created on: Aug 27, 2013
 *      Author: lucas
 */

#include "MapObject.h"


MapObject::MapObject(object_type type):Object(type) {
	tail = Tail();
	parent = NULL;
	hitable = true;
}


