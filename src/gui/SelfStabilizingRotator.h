#ifndef SRC_GUI_SELFSTABILIZINGROTATOR_H_
#define SRC_GUI_SELFSTABILIZINGROTATOR_H_

#include <boost/date_time.hpp>

class SelfStabilizingRotator
{
	public:
		SelfStabilizingRotator();
		virtual ~SelfStabilizingRotator();

		void update();
		void applyRotation();
		void addXRotation(float angle);
		void addYRotation(float angle);
		void addZRotation(float angle);

	private:

		static void moveCloserZero(float& x, float change);
		static void changeMaxToFromZero(float &x , float change, float max);

		float _x;
		float _y;
		float _z;

		float _maxRotation;
		float returnSpeed;
		boost::posix_time::ptime lastUpdate;
};

#endif /* SRC_GUI_SELFSTABILIZINGROTATOR_H_ */
