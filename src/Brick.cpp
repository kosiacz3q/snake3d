#include "Brick.h"
#include "ShapeGenerator.h"

Brick::Brick()
	:color_normal_vertex(nullptr),
	 indexTable(nullptr),
	 edgelength(1)
{
	position = Vector3f(0, 0, 0);
	rotation = Vector3f(0, 0, 0);
}

Brick::~Brick()
{
	if (color_normal_vertex != nullptr)
		delete[] color_normal_vertex;

	if (indexTable != nullptr)
		delete[] indexTable;
}

void Brick::draw()
{
	//TODO
	/*
	glPushMatrix();

	glTranslatef(this->position.x, this->position.y, this->position.z);

	glRotatef(this->rotation.x, 0., 1., 0.);
	glRotatef(this->rotation.y, 1., 0., 0.);
	glRotatef(this->rotation.z, 0., 0., 1.);

	glInterleavedArrays(GL_C4F_N3F_V3F, 0, this->color_normal_vertex);
	glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, this->indexTable);

	glPopMatrix();*/
}

void Brick::update()
{

}

void Brick::init()
{
	color_normal_vertex = new float[80];
	indexTable = new GLubyte[36];

	ShapeGenerator::getSquare(color_normal_vertex, edgelength, Colors::HotPink);
	ShapeGenerator::setStandartSquareIndexTable(indexTable);
}

void Brick::setPosition(const Vector3f& pos)
{
	this->position = Vector3f(pos);
}

void Brick::move(const Vector3f& shift)
{
	this->position += shift;
}

void Brick::setRotation(const Vector3f& rot)
{
	this->rotation = Vector3f(rot);
}

void Brick::rotate(const Vector3f& shrot)
{
	this->rotation += shrot;
}

void Brick::setColor(const float* color)
{
	ShapeGenerator::setColorOnSquare(color_normal_vertex, 8, color);
}

void Brick::setEdgeLength(float length)
{
	edgelength = length;
}

void Brick::goLsdGo()
{
	ShapeGenerator::LSDonGL_C4F_N3F_V3F(color_normal_vertex, 8);
}
