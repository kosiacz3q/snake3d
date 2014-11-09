#ifndef SRC_GUI_FLICKERINGCOLOR_H_
#define SRC_GUI_FLICKERINGCOLOR_H_

#include <boost/date_time.hpp>

class FlickeringColor
{
	public:
		FlickeringColor(int time,const float* color);
		virtual ~FlickeringColor();
		void update();
		float* getColor();
	private:
		float* flickeringColor;
		boost::posix_time::ptime lastUpdate;
		int multipiler;
		float cycleMiliseconds;
};

#endif /* SRC_GUI_FLICKERINGCOLOR_H_ */
