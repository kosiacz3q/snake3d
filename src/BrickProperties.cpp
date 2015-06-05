#include "BrickProperties.h"

BrickProperties::BrickProperties(Vector4f pos, const GLfloat* col)
{
	this->position = Vector4f(pos);
	this->color = col;
}

BrickProperties::BrickProperties()
{
	this->position = Vector4f();
	this->color = nullptr;
}
