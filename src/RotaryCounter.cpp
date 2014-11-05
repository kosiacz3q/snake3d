#include "RotaryCounter.h"
#include <string>
#include "Colors.h"
#include "StringHandler.h"

GLuint RotaryCounter::textureHandlers[10];
bool RotaryCounter::isInitiated = false;
Texture RotaryCounter::tex[10];

Vector3f RotaryCounter::Section::edges[2][10];

RotaryCounter::RotaryCounter(Vector3f& position)
{
	if (!isInitiated)
	{
		RotaryCounter::init();
		isInitiated = true;
	}

	this->position = position;
	this->value = 0;
	this->rotation = Vector3f();

	countOfSections = 5;

	for (int i = 0; i < countOfSections; ++i)
		sections[i].actualNumber = 0;

}

RotaryCounter::~RotaryCounter()
{

}

void RotaryCounter::free()
{
	for (int i = 0; i < 10; ++i)
		tex[i].freeTexture();

	isInitiated = false;
}

void RotaryCounter::init()
{
	tex[0].loadTextureFromFile("tex/tex_0.png");
	tex[1].loadTextureFromFile("tex/tex_1.png");
	tex[2].loadTextureFromFile("tex/tex_2.png");
	tex[3].loadTextureFromFile("tex/tex_3.png");
	tex[4].loadTextureFromFile("tex/tex_4.png");
	tex[5].loadTextureFromFile("tex/tex_5.png");
	tex[6].loadTextureFromFile("tex/tex_6.png");
	tex[7].loadTextureFromFile("tex/tex_7.png");
	tex[8].loadTextureFromFile("tex/tex_8.png");
	tex[9].loadTextureFromFile("tex/tex_9.png");

	Section::edges[0][0] = Vector3f(-.5, 1, 0);
	Section::edges[1][0] = Vector3f(.5, 1, 0);
	Section::edges[0][1] = Vector3f(-.5, .86, .5);
	Section::edges[1][1] = Vector3f(.5, .86, .5);
	Section::edges[0][2] = Vector3f(-.5, .5, .86);
	Section::edges[1][2] = Vector3f(.5, .5, .86);
	Section::edges[0][3] = Vector3f(-.5, -.5, .86);
	Section::edges[1][3] = Vector3f(.5, -.5, .86);
	Section::edges[0][4] = Vector3f(-.5, -.86, .5);
	Section::edges[1][4] = Vector3f(.5, -.86, .5);
	Section::edges[0][5] = Vector3f(-.5, -1, 0);
	Section::edges[1][5] = Vector3f(.5, -1, 0);
	Section::edges[0][6] = Vector3f(-.5, -.86, -.5);
	Section::edges[1][6] = Vector3f(.5, -.86, -.5);
	Section::edges[0][7] = Vector3f(-.5, -.5, -.86);
	Section::edges[1][7] = Vector3f(.5, -.5, -.86);
	Section::edges[0][8] = Vector3f(-.5, .5, -.86);
	Section::edges[1][8] = Vector3f(.5, .5, -.86);
	Section::edges[0][9] = Vector3f(-.5, .86, -.5);
	Section::edges[1][9] = Vector3f(.5, .86, -.5);
}

void RotaryCounter::draw()
{

	glPushMatrix();

	glTranslatef(this->position.x, this->position.y, this->position.z);

	glScalef(0.3, 0.3, 0.3);

	glRotatef(rotation.x, 0., 1., 0.);
	glRotatef(rotation.y, 1., 0., 0.);
	glRotatef(rotation.z, 0., 0., 1.);

	glEnable(GL_TEXTURE_2D);

	for (int sectionNumber = 0; sectionNumber < countOfSections; ++sectionNumber)
	{
		glPushMatrix();
		glRotatef(-sections[sectionNumber].actualNumber * 36, 1., 0., 0.);
		for (int i = 0; i < 10; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, tex[i].mTextureID);

			if (sections[sectionNumber].numberToReach == i)
				glColor4fv(Colors::Khaki);
			else
				glColor4fv(Colors::PeachPuff);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);
			glVertex3f(Section::edges[0][i].x, Section::edges[0][i].y, Section::edges[0][i].z); //upper left
			glTexCoord2f(1.0, 0.0);
			glVertex3f(Section::edges[1][i].x, Section::edges[1][i].y, Section::edges[1][i].z); //upper right
			glTexCoord2f(1.0, 1.0);
			glVertex3f(Section::edges[1][(i + 1) % 10].x, Section::edges[1][(i + 1) % 10].y, Section::edges[1][(i + 1) % 10].z); //bottom right
			glTexCoord2f(0.0, 1.0);
			glVertex3f(Section::edges[0][(i + 1) % 10].x, Section::edges[0][(i + 1) % 10].y, Section::edges[0][(i + 1) % 10].z); //bottom left
			glEnd();
		}

		glPopMatrix();
		glTranslatef(1.1, 0, 0);
	}
	//glBindTexture(GL_TEXTURE_2D , NULL);

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void RotaryCounter::setRotation(const Vector3f& rot)
{
	rotation = Vector3f(rot);
}

void RotaryCounter::drawString(const char* seq, int length)
{

	glColor4fv(Colors::DarkBlue);

	glRasterPos3f((GLfloat) this->position.x, (GLfloat) this->position.y, (GLfloat) this->position.z);

	for (int i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, seq[i]);
	}
}

void RotaryCounter::addPoints(int howMany)
{
	value += howMany;

	int tempValue = value;

	for (int i = 0; i < countOfSections; ++i)
	{
		sections[countOfSections - i - 1].numberToReach = tempValue % 10;
		tempValue /= 10;
	}

}

void RotaryCounter::update(int mili)
{
	for (int i = 0; i < countOfSections; ++i)
	{
		if (sections[i].numberToReach != sections[i].actualNumber)
		{
			sections[i].actualNumber += mili / 500.;

			if (sections[i].actualNumber >= 10)
				sections[i].actualNumber -= 10;

			if ((sections[i].numberToReach - sections[i].actualNumber) <= 0 && (sections[i].numberToReach - sections[i].actualNumber) > -1)
			{
				sections[i].actualNumber = sections[i].numberToReach;
			}
		}
	}
}
