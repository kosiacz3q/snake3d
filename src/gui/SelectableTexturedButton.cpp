#include "SelectableTexturedButton.h"

#include <GL/freeglut.h>
#include <boost/random.hpp>

int SelectableTexturedButton::idCounter = 0;

SelectableTexturedButton::SelectableTexturedButton(Vector3f posittion, Vector2f dimensions, std::string path,const float* selectionColor)
		: _positon(posittion), _dimensions(dimensions), _isSelected(false), _color(selectionColor), id(++idCounter)
{
	_texture = new Texture();
	_texture->loadTextureFromFile(path);

	initZAxis();
}

SelectableTexturedButton::~SelectableTexturedButton()
{
	_texture->freeTexture();
	delete _texture;
}

void SelectableTexturedButton::draw()
{
	glPushMatrix();

	glTranslatef(_positon.x, _positon.y, _positon.z);

	if (_isSelected)
	{
		glColor4fv(_color);
		glBegin(GL_QUADS);

		glVertex3f(-_dimensions.x * 0.1, _dimensions.y * 0.1  		, -_z0);
		glVertex3f( _dimensions.x * 1.1,   _dimensions.y * 0.1  	, -_z1);
		glVertex3f( _dimensions.x * 1.1, -_dimensions.y * 1.1 		, -_z2);
		glVertex3f( -_dimensions.x * 0.1 , -_dimensions.y * 1.1 	, -_z3);

		glEnd();
	}

	glColor4fv(Colors::Transparent);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texture->mTextureID);
	glBegin(GL_QUADS);

	glTexCoord2f(0.01, 0.01);
	glVertex3f(0, 0, 0);
	glTexCoord2f(0.99, 0.01);
	glVertex3f(_dimensions.x, 0, 0);
	glTexCoord2f(0.99, 0.99);
	glVertex3f(_dimensions.x, -_dimensions.y, 0);
	glTexCoord2f(0.01, 0.99);
	glVertex3f(0, -_dimensions.y, 0);

	glEnd();


	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void SelectableTexturedButton::drawSelection()
{
	glPushMatrix();
	glPushName(id);

	glTranslatef(_positon.x, _positon.y, _positon.z);

	glBegin(GL_QUADS);

	glVertex3f(0, 0, 0);

	glVertex3f(_dimensions.x, 0, 0);

	glVertex3f(_dimensions.x, -_dimensions.y, 0);

	glVertex3f(0, -_dimensions.y, 0);

	glEnd();
	glPopName();
	glPopMatrix();
}

void SelectableTexturedButton::setSelected(bool selected)
{
	if (!_isSelected)
		initZAxis();

	_isSelected = selected;
}

bool SelectableTexturedButton::isSelected()
{
	return _isSelected;
}

bool SelectableTexturedButton::contains(float x, float y)
{
	if( x >= _positon.x && x <= _positon.x + _dimensions.x
	 && y <= _positon.y && y >= _positon.y - _dimensions.y )
		return true;

	return false;
}

void SelectableTexturedButton::initZAxis()
{
	boost::mt19937 generator(time(0) + (int)(_z0 * 1000));
	boost::uniform_real<float> u01;

	_z0 = u01(generator) * 2 / 10;
	_z1 = u01(generator) * 2 / 10;
	_z2 = u01(generator) * 2 / 10;
	_z3 = u01(generator) * 2 / 10;

}

int SelectableTexturedButton::getId()
{
	return id;
}
