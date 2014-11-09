#include "FlickeringColor.h"

FlickeringColor::FlickeringColor(int cycleDuration,const float* color)
{
	flickeringColor = new float[4]
	{ color[0], color[1], color[2], 0.000000 };
	lastUpdate = boost::posix_time::microsec_clock::local_time();
	multipiler = 1;
	cycleMiliseconds = cycleDuration;
}

FlickeringColor::~FlickeringColor()
{
	delete[] flickeringColor;
}

float* FlickeringColor::getColor()
{
	return flickeringColor;
}

void FlickeringColor::update()
{
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration diff = now - lastUpdate;
	lastUpdate = now;

	flickeringColor[3] += (float)multipiler * diff.total_milliseconds() / cycleMiliseconds;

	if (flickeringColor[3] >= 1)
	{
		flickeringColor[3] = 1;
		multipiler = -1;
	}
	else if (flickeringColor[3] <= 0)
	{
		flickeringColor[3] = 0;
		multipiler = 1;
	}
}

