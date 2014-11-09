#include "SelfStabilizingRotator.h"

#include <GL/freeglut.h>

SelfStabilizingRotator::SelfStabilizingRotator()
		: _x(0), _y(0), _z(0), _maxRotation(1), returnSpeed(2)
{
	lastUpdate = boost::posix_time::microsec_clock::local_time();
}

SelfStabilizingRotator::~SelfStabilizingRotator()
{

}

void SelfStabilizingRotator::update()
{
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = now - lastUpdate;
	lastUpdate = now;

	float change = returnSpeed * diff.total_milliseconds() / 1000;

	moveCloserZero(_x, change);
	moveCloserZero(_y, change);
	moveCloserZero(_z, change);
}

void SelfStabilizingRotator::moveCloserZero(float& x, float change)
{
	if (x > 0)
	{
		if ((x -= change) < 0)
		{
			x = 0;
		}
	}
	else if (x < 0)
	{
		if ((x += change) > 0)
		{
			x = 0;
		}
	}
}

void SelfStabilizingRotator::applyRotation()
{
	glRotatef(_x, 1, 0, 0);
	glRotatef(_y, 0, 1, 0);
	glRotatef(_z, 0, 0, 1);
}

void SelfStabilizingRotator::changeMaxToFromZero(float &x, float change, float max)
{
	x += change;

	if (x > max)
		x = max;
	else if (x < -max)
		x = -max;
}

void SelfStabilizingRotator::addXRotation(float angle)
{
	changeMaxToFromZero(_x, angle * (1 - _x / _maxRotation ), _maxRotation);
}

void SelfStabilizingRotator::addYRotation(float angle)
{
	changeMaxToFromZero(_y, angle * (1 - _y / _maxRotation ), _maxRotation);
}

void SelfStabilizingRotator::addZRotation(float angle)
{
	changeMaxToFromZero(_z, angle * (1 - _z / _maxRotation ), _maxRotation);
}

