#include <math.h>
#include <string.h>
#include  <stdio.h>
#include <boost/random.hpp>

#include "ShapeGenerator.h"

ShapeGenerator::ShapeGenerator()
{
}

void ShapeGenerator::getSquare(float* targetContainer, const float edgeLenght, const float* color)
{

	/*INFO
	 * content type :  GL_C4F_N3F_V3F   color4 normal3 position3
	 * targetContainer [ colorR(0) , colorG(1) , colorB(2) ,colorA(3) , normalX(4), normalY(5) , normalZ(6) , posX(7) , pos Y(8) , posZ(9)  ]
	 * 0 -++
	 * 1 +++
	 * 2 +-+
	 * 3 --+
	 * 4 -+-
	 * 5 ++-
	 * 6 +--
	 * 7 ---
	 */

	const float halfLenght = edgeLenght / 2;

	memcpy(&targetContainer[0], color, 16); //0  color
	targetContainer[7] = -halfLenght;
	targetContainer[8] = halfLenght;
	targetContainer[9] = halfLenght;

	memcpy(&targetContainer[10], color, 16); //1  color
	targetContainer[17] = halfLenght;
	targetContainer[18] = halfLenght;
	targetContainer[19] = halfLenght;

	memcpy(&targetContainer[20], color, 16); //2  color
	targetContainer[27] = halfLenght;
	targetContainer[28] = -halfLenght;
	targetContainer[29] = halfLenght;

	memcpy(&targetContainer[30], color, 16); //3  color
	targetContainer[37] = -halfLenght;
	targetContainer[38] = -halfLenght;
	targetContainer[39] = halfLenght;

	memcpy(&targetContainer[40], color, 16); //4  color
	targetContainer[47] = -halfLenght;
	targetContainer[48] = halfLenght;
	targetContainer[49] = -halfLenght;

	memcpy(&targetContainer[50], color, 16); //5  color
	targetContainer[57] = halfLenght;
	targetContainer[58] = halfLenght;
	targetContainer[59] = -halfLenght;

	memcpy(&targetContainer[60], color, 16); //6  color
	targetContainer[67] = halfLenght;
	targetContainer[68] = -halfLenght;
	targetContainer[69] = -halfLenght;

	memcpy(&targetContainer[70], color, 16); //7  color
	targetContainer[77] = -halfLenght;
	targetContainer[78] = -halfLenght;
	targetContainer[79] = -halfLenght;

	float* tmpNormal = new float[3];

	//0 normal
	getNormal3f3v(tmpNormal, &targetContainer[7], &targetContainer[17], &targetContainer[37], &targetContainer[47]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[4], tmpNormal, 12);
	//1 normal
	getNormal3f3v(tmpNormal, &targetContainer[17], &targetContainer[7], &targetContainer[27], &targetContainer[57]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[14], tmpNormal, 12);
	//2 normal
	getNormal3f3v(tmpNormal, &targetContainer[27], &targetContainer[17], &targetContainer[37], &targetContainer[67]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[24], tmpNormal, 12);
	//3 normal
	getNormal3f3v(tmpNormal, &targetContainer[37], &targetContainer[7], &targetContainer[27], &targetContainer[77]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[34], tmpNormal, 12);
	//4 normal
	getNormal3f3v(tmpNormal, &targetContainer[47], &targetContainer[7], &targetContainer[57], &targetContainer[77]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[44], tmpNormal, 12);
	//5 normal
	getNormal3f3v(tmpNormal, &targetContainer[57], &targetContainer[47], &targetContainer[67], &targetContainer[17]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[54], tmpNormal, 12);
	//6 normal
	getNormal3f3v(tmpNormal, &targetContainer[67], &targetContainer[57], &targetContainer[77], &targetContainer[27]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[64], tmpNormal, 12);
	//7 normal
	getNormal3f3v(tmpNormal, &targetContainer[77], &targetContainer[47], &targetContainer[67], &targetContainer[37]);
	reverseNormal(tmpNormal);
	memcpy(&targetContainer[74], tmpNormal, 12);

	delete tmpNormal;
}

void ShapeGenerator::getNormal3f3v(float* dest, const float* src, const float* ver1, const float* ver2, const float* ver3)
{

	dest[0] = (ver1[0] + ver2[0] + ver3[0] - 3 * src[0]) / 3;
	dest[1] = (ver1[1] + ver2[1] + ver3[1] - 3 * src[1]) / 3;
	dest[2] = (ver1[2] + ver2[2] + ver3[2] - 3 * src[2]) / 3;

	normalize(dest);
}

void ShapeGenerator::normalize(float* vec)
{
	float lenght = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);

	vec[0] /= lenght;
	vec[1] /= lenght;
	vec[2] /= lenght;
}

void ShapeGenerator::reverseNormal(float* vec)
{
	vec[0] = -vec[0];
	vec[1] = -vec[1];
	vec[2] = -vec[2];
}

void ShapeGenerator::setStandartSquareIndexTable(GLubyte* table)
{
	//t1
	table[0] = 0;
	table[1] = 1;
	table[2] = 2;
	//t2
	table[3] = 0;
	table[4] = 2;
	table[5] = 3;
	//t3
	table[6] = 0;
	table[7] = 3;
	table[8] = 4;
	//t4
	table[9] = 4;
	table[10] = 3;
	table[11] = 7;
	//t5
	table[12] = 4;
	table[13] = 1;
	table[14] = 0;
	//t6
	table[15] = 4;
	table[16] = 5;
	table[17] = 1;
	//t7
	table[18] = 1;
	table[19] = 5;
	table[20] = 6;
	//t8
	table[21] = 1;
	table[22] = 6;
	table[23] = 2;
	//t9
	table[24] = 3;
	table[25] = 2;
	table[26] = 6;
	//t10
	table[27] = 3;
	table[28] = 6;
	table[29] = 7;
	//t11
	table[30] = 7;
	table[31] = 6;
	table[32] = 5;
	//t12
	table[33] = 7;
	table[34] = 5;
	table[35] = 4;
}

void ShapeGenerator::getDebugInfo(const float* tab, int width, int height)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width - 1; ++j)
			printf(" %f ,", tab[j + i * (width)]);
		printf(" %f\n", tab[width - 1 + i * (width)]);
	}
}

void ShapeGenerator::LSDonGL_C4F_N3F_V3F(float* tab, int height)
{
	boost::mt19937 generator(time(0));
	for (int i = 0; i < height; ++i)
	{
		boost::uniform_real<float> u01;
		tab[(i * 10) + 0] = u01(generator);
		tab[(i * 10) + 1] = u01(generator);
		tab[(i * 10) + 2] = u01(generator);
	}
}

void ShapeGenerator::setColorOnSquare(float* tab, int height, const GLfloat* color)
{
	for (int i = 0; i < height; ++i)
	{
		memcpy(&tab[(i * 10)], color, 4 * 4);
	}
}

void ShapeGenerator::destructEffect_propagation(float* targetContainer, float shift)
{
	targetContainer[7] -= shift;
	targetContainer[8] += shift;
	targetContainer[9] += shift;

	targetContainer[17] += shift;
	targetContainer[18] += shift;
	targetContainer[19] += shift;

	targetContainer[27] += shift;
	targetContainer[28] -= shift;
	targetContainer[29] += shift;

	targetContainer[37] -= shift;
	targetContainer[38] -= shift;
	targetContainer[39] += shift;

	targetContainer[47] -= shift;
	targetContainer[48] += shift;
	targetContainer[49] -= shift;

	targetContainer[57] += shift;
	targetContainer[58] += shift;
	targetContainer[59] -= shift;

	targetContainer[67] += shift;
	targetContainer[68] -= shift;
	targetContainer[69] -= shift;

	targetContainer[77] -= shift;
	targetContainer[78] -= shift;
	targetContainer[79] -= shift;
}
