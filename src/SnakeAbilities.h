#ifndef SNAKEABILITIES_H_
#define SNAKEABILITIES_H_

#include <GL/gl.h>
#include <GL/freeglut.h>
#include "Texture.h"
#include "MessagePack.h"
#include "Vectorf.h"

class SnakeAbilities
{
	public:
		SnakeAbilities(const Vector3f& vec);
		static void init();
		static void free();
		void draw();

		void setRotation(const Vector3f vec);

		virtual ~SnakeAbilities();
		void setActiveAbility(Message::Notification);

	private:
		Vector3f position;
		Vector3f rotation;
		Message::Notification activeBoost;
		static Texture jumpTexture;
		static Texture speedTexture;

};

#endif /* SNAKEABILITIES_H_ */
