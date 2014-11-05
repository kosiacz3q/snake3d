#include "Vectorf.h"

Vector3f::Vector3f()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3f::Vector3f(const float& xp, const float& yp, const float& zp)
{
	x = xp;
	y = yp;
	z = zp;
}

Vector3f Vector3f::operator+(const Vector3f& vec)
{
	return Vector3f(x + vec.x, y + vec.y, z + vec.z);
}

void Vector3f::operator+=(const Vector3f& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

Vector3f Vector3f::operator-(const Vector3f& vec)
{
	return Vector3f(x - vec.x, y - vec.y, z - vec.z);
}

void Vector3f::operator-=(const Vector3f& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

void Vector3f::smooth(Vector3f vec, float maxDiff)
{
	if (this->x > vec.x)
	{
		if (this->x < vec.x + maxDiff)
			this->x = vec.x;
	}
	else
	{
		if (this->x > vec.x - maxDiff)
			this->x = vec.x;
	}

	if (this->y > vec.y)
	{
		if (this->y < vec.y + maxDiff)
			this->y = vec.y;
	}
	else
	{
		if (this->y > vec.y - maxDiff)
			this->y = vec.y;
	}

	if (this->z > vec.z)
	{
		if (this->z < vec.z + maxDiff)
			this->z = vec.z;
	}
	else
	{
		if (this->z > vec.z - maxDiff)
			this->z = vec.z;
	}
}

void Vector3f::fillVector(Vector3f src, Vector3f& dest, float part)
{
	dest += (src * part);

	if (dest.x > src.x)
		dest.x = src.x;
	if (dest.y > src.y)
		dest.y = src.y;
	if (dest.z > src.z)
		dest.z = src.z;
}

void Vector3f::moveCloseToVector(Vector3f toReach, Vector3f& actual, float part)
{

	if (actual.x < toReach.x)
	{
		actual.x += ((toReach.x - actual.x) * part);
		if (actual.x > toReach.x)
			actual.x = toReach.x;
	}
	else
	{
		actual.x -= ((actual.x - toReach.x) * part);
		if (actual.x < toReach.x)
			actual.x = toReach.x;
	}

	if (actual.y < toReach.y)
	{
		actual.y += ((toReach.y - actual.y) * part);
		if (actual.y > toReach.y)
			actual.y = toReach.y;
	}
	else
	{
		actual.y -= ((actual.y - toReach.y) * part);
		if (actual.y < toReach.y)
			actual.y = toReach.y;
	}

	if (actual.z < toReach.z)
	{
		actual.z += ((toReach.z - actual.z) * part);
		if (actual.z > toReach.z)
			actual.z = toReach.z;
	}
	else
	{
		actual.z -= ((actual.z - toReach.z) * part);
		if (actual.z < toReach.z)
			actual.z = toReach.z;
	}
}

bool Vector3f::operator==(const Vector3f& vec)
{
	if (x == vec.x)
		if (y == vec.y)
			if (z == vec.z)
				return true;
	return false;
}

void Vector3f::operator*=(const float& c)
{
	x *= c;
	y *= c;
	z *= c;
}

void Vector3f::operator*=(const int& c)
{
	x *= c;
	y *= c;
	z *= c;
}

Vector3f Vector3f::operator*(const float& c)
{
	return Vector3f(this->x * c, this->y * c, this->z * c);
}

Vector2f::Vector2f(const float& xp, const float& yp)
{
	this->x = xp;
	this->y = yp;
}
Vector2f Vector2f::operator+(const Vector2f& vec)
{
	return Vector2f(vec.x + this->x, vec.y + this->y);
}

void Vector2f::operator+=(const Vector2f& vec)
{
	this->x += vec.x;
	this->y += vec.y;
}

Vector2f Vector2f::operator-(const Vector2f& vec)
{
	return Vector2f(this->x - vec.x, this->y - vec.y);
}
void Vector2f::operator-=(const Vector2f& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
}

bool Vector2f::operator==(const Vector2f& vec)
{
	if (vec.x == this->x && vec.y == this->y)
		return true;
	return false;
}

void Vector2f::operator*=(const float& c)
{
	this->x *= c;
	this->y *= c;
}

void Vector2f::operator*=(const int& c)
{
	this->x *= c;
	this->y *= c;
}
Vector2f::Vector2f()
{
	this->x = 0;
	this->y = 0;
}

Vector4f::Vector4f()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4f::Vector4f(const float& xp, const float& yp, const float& zp, const float& wp)
{
	x = xp;
	y = yp;
	z = zp;
	w = wp;
}

Vector4f Vector4f::operator+(const Vector4f& vec)
{
	return Vector4f(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

void Vector4f::operator+=(const Vector4f& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
}

Vector4f Vector4f::operator-(const Vector4f& vec)
{
	return Vector4f(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

void Vector4f::operator-=(const Vector4f& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
}

bool Vector4f::operator==(const Vector4f& vec)
{
	if (w == vec.w)
		if (x == vec.x)
			if (y == vec.y)
				if (z == vec.z)
					return true;
	return false;
}

void Vector4f::operator*=(const float& c)
{
	x *= c;
	y *= c;
	z *= c;
	w *= c;
}

void Vector4f::operator*=(const int& c)
{
	x *= c;
	y *= c;
	z *= c;
	w *= c;
}

Vector3f::Vector3f(Vector4f vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

Vector3f Vector3f::getPartOfDiffrence(Vector3f vec1, Vector3f vec2, float part)
{
	return (vec1 - vec2) * part;
}
