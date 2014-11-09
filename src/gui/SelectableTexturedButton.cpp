#include "SelectableTexturedButton.h"

#include <GL/freeglut.h>



SelectableTexturedButton::SelectableTexturedButton(Vector3f posittion, Vector2f dimensions, std::string path,const float* selectionColor)
		: _positon(posittion), _dimensions(dimensions), _isSelected(false), _color(selectionColor)
{
	_texture = new Texture();
	_texture->loadTextureFromFile(path);
}

SelectableTexturedButton::~SelectableTexturedButton()
{

}

void SelectableTexturedButton::draw()
{
	glPushMatrix();

	glTranslatef(_positon.x, _positon.y, _positon.z);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texture->mTextureID);

	if (_isSelected)
		glColor4fv(_color);
	else
		glColor4fv(Colors::Transparent);

	glBegin(GL_QUADS);

	glTexCoord2f(0.01, 0.01);
	glVertex3f(0, 0, 0); //upper left
	glTexCoord2f(0.99, 0.01);
	glVertex3f(0, _dimensions.y, 0); //upper right
	glTexCoord2f(0.99, 0.99);
	glVertex3f(_dimensions.x, -_dimensions.y, 0); //bottom right
	glTexCoord2f(0.01, 0.99);
	glVertex3f(-_dimensions.x, -_dimensions.y, 0); //bottom left

	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void SelectableTexturedButton::setSelected(bool selected)
{
	_isSelected = selected;
}

bool SelectableTexturedButton::isSelected()
{
	return _isSelected;
}
