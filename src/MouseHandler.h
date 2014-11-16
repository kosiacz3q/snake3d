#ifndef MOUSEHANDLER_H_
#define MOUSEHANDLER_H_

#include "Vectorf.h"

class MouseHandler
{
	public:
		MouseHandler();
		virtual ~MouseHandler();

		void setMousePosition(const int& x, const int& y);

		void setLeftButtonState(int state)
		{
			leftButtonState = state;
		}

		void setRightButtonState(int state)
		{
			rightButtonState = state;
		}

	private:
		int leftButtonState;
		int rightButtonState;

		Vector2f actualPosition;
		Vector2f lastPosition;

};

#endif /* MOUSEHANDLER_H_ */
