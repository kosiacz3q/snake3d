#include "MapObject.h"

MapObject::MapObject(object_type type)
		: Object(type)
{
	tail = Tail();
	parent = NULL;
	hitable = true;
}

