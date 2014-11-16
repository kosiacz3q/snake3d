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

		void setPosition(const Vector3f& pos);
		void setRotation(const Vector3f& rot);
		void rotate(const Vector3f& shrot);
		void move(const Vector3f& shift);

		Vector3f getPosition()
		{
			return position;
		}

		Vector3f getRotation()
		{
			return rotation;
		}

		void setColor(const float* color);

		void setEdgeLength(float length);

		void goLsdGo();

		float getEdgeLength()
		{
			return edgelength;
		}

	protected:
		Brick(object_type type);
	private:
		Vector3f position;
		Vector3f rotation;

		float* color_normal_vertex;
		GLubyte* indexTable;
		float edgelength;
};

#endif // BRICK_H
