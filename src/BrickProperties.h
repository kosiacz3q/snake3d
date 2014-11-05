#ifndef BRICKPROPERTIES_H_
#define BRICKPROPERTIES_H_

#include "Vectorf.h"
#include <GL/gl.h>

class BrickProperties
{
	public:
		BrickProperties(Vector4f pos, const GLfloat* col);
		BrickProperties();
		Vector4f position;
		const GLfloat* color;
};

#endif /* BRICKPROPERTIES_H_ */
