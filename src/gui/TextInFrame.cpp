#include "TextInFrame.h"

#include <GL/freeglut.h>

#include "StringDrawer.h"
#include "../Colors.h"

//#include "../Colors.h"

TextInFrame::TextInFrame(Vector3f position , Vector2f dimmensions, std::string text, const float* frameColor)
	:position(position), dimmensions(dimmensions), text(text), frameColor(frameColor)
{

}


void TextInFrame::draw()
{
	glPushMatrix();

	glTranslatef(position.x, position.y, position.z);

	StringDrawer::drawString(text,0.1,-0.2,0);

	glColor4fv(frameColor);

	glBegin(GL_QUADS);

	glVertex3f(0, 0, -0.05); //upper left

	glVertex3f(dimmensions.x, 0, -0.05); //upper right

	glVertex3f(dimmensions.x, -dimmensions.y, -0.05); //bottom right

	glVertex3f(0, -dimmensions.y, -0.05); //bottom left

	glEnd();

	glPopMatrix();
}
