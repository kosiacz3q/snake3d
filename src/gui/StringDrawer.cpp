/*
 * StringDrawer.cpp
 *
 *  Created on: 8 Nov 2014
 *      Author: lucas
 */

#include "StringDrawer.h"

#include <GL/glut.h>
#include "../Colors.h"

#include <boost/foreach.hpp>

StringDrawer::StringDrawer()
{
	// TODO Auto-generated constructor stub

}

StringDrawer::~StringDrawer()
{
	// TODO Auto-generated destructor stub
}

void StringDrawer::drawString(const std::string text, const float x, const float y, const float z, void* font,const float* color)
{
	if (color == nullptr)
		glColor4fv(Colors::DarkBlue);
	else
		glColor4fv(color);


	glRasterPos3f((GLfloat) x, (GLfloat) y, (GLfloat) z);

	if (font == nullptr)
		font = GLUT_BITMAP_TIMES_ROMAN_24;

	BOOST_FOREACH(char c , text)
	{
		glutBitmapCharacter(font, c);
		//glutStrokeCharacter(font , c);
	}
}

void StringDrawer::strokeString(const std::string text, const float x, const float y, const float z, void* font,const float* color)
{
	if (color == nullptr)
		glColor4fv(Colors::DarkBlue);
	else
		glColor4fv(color);


	glRasterPos3f((GLfloat) x, (GLfloat) y, (GLfloat) z);

	if (font == nullptr)
		font = GLUT_STROKE_ROMAN;



	BOOST_FOREACH(char c , text)
	{
		glutStrokeCharacter(font , c);
	}
}

