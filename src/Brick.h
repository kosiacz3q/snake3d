#ifndef BRICK_H
#define BRICK_H

#include "Object.h"

class Brick
{
	public:
		Brick();
		virtual ~Brick();

		void draw();
		void update();
		void init();

		float* color_normal_vertex;
		GLubyte* indexTable;

		void setPosition(const Vector3f& pos);
		void setRotation(const Vector3f& rot);
		void rotate(const Vector3f& shrot);
		void move(const Vector3f& shift);
		Vector3f position;
		Vector3f rotation;
	protected:
		Brick(object_type type);
	private:

};

#endif // BRICK_H
