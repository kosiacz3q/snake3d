#ifndef ROTARYCOUNTER_H_
#define ROTARYCOUNTER_H_

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "Vectorf.h"
#include "Texture.h"

class RotaryCounter
{
	public:
		RotaryCounter(Vector3f& position);
		~RotaryCounter();

		void draw();
		static void init();
		static void free();
		void setRotation(const Vector3f& rot);
		void addPoints(int howMany);
		void update(int mili);
		int getValue();

	private:
		struct Section
		{
			public:
				Section()
				{
					mustReachTen = false;
					actualNumber = 0;
					numberToReach = 0;
				}
				;

				float actualNumber;
				int numberToReach;
				bool mustReachTen;
				static Vector3f edges[2][10];
		};

		int countOfSections;
		Section sections[10];
		Vector3f position;
		Vector3f rotation;
		int value;
		static bool isInitiated;
		static GLuint textureHandlers[10];
		static Texture tex[10];
};

#endif /* ROTARYCOUNTER_H_ */
