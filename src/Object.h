#ifndef OBJECT_H
#define OBJECT_H

#include <boost/date_time.hpp>
#include <GL/freeglut.h>

#include "Vectorf.h"

enum object_type
{
	BRICK, MAIN_BRICK, SNAKE, OBSTACLE, GAINER, MOCK,
};

class Object
{
	public:
		Object(const object_type& t);
		virtual ~Object();

		long int getID() const;
		object_type getType() const;
		virtual void update(int miliseconds) = 0;
		virtual void init() = 0;

	protected:
		object_type type;
		long int ID;
		Vector2f rotation;
		Vector3f position;

	private:

		static long int _idCounter;
};

#endif // OBJECT_H
