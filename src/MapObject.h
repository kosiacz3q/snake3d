#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include <list>

#include "Object.h"
#include "BrickProperties.h"
#include "IMessager.h"

typedef std::list<BrickProperties> Tail;

class MapObject: public Object, public IMessager
{
	public:
		MapObject(object_type type);

		void setHitable(bool isHitable)
		{
			hitable = isHitable;
		}

		bool isHitable()
		{
			return hitable;
		}

		Tail& getTail()
		{
			return tail;
		}

		void setParent(IMessager* parent)
		{
			this->parent = parent;
		}

	protected:

		bool hitable;
		Tail tail;
		IMessager* parent;
};

#endif /* MAPOBJECT_H_ */
