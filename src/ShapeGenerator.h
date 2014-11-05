#ifndef SHAPEGENERATOR_H_
#define SHAPEGENERATOR_H_

#include "Colors.h"

class ShapeGenerator
{
	public:

		static void getSquare(float* targetContainer, const float edgeLenght, const float* color);
		static void setStandartSquareIndexTable(GLubyte* table);
		static void getNormal3f3v(float* dest, const float* src, const float* ver1, const float* ver2, const float* ver3);
		static void LSDonGL_C4F_N3F_V3F(float* tab, int height);
		static void normalize(float* vec);
		static void reverseNormal(float* vec);
		static void getDebugInfo(const float* tab, int width, int height);
		static void setColorOnSquare(float* tab, int height, const GLfloat* color);
		static void destructEffect_propagation(float* targetContainer, float shift);
	private:
		ShapeGenerator();
};

#endif /* SHAPEGENERATOR_H_ */
