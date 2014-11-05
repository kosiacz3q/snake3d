#include "Object.h"

long int Object::_idCounter = 1;

Object::Object(const object_type& t)
{
	this->ID = Object::_idCounter++;
	this->type = t;
}

Object::~Object()
{

}

long int Object::getID() const
{
	return this->ID;
}

object_type Object::getType() const
{
	return this->type;
}

