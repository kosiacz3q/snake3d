#ifndef SRC_GUI_TEXTINFRAME_H_
#define SRC_GUI_TEXTINFRAME_H_

#include <string>

#include "../Vectorf.h"

class TextInFrame
{
	public:
		TextInFrame(Vector3f position , Vector2f dimmensions, std::string text,const float* frameColor);
		virtual ~TextInFrame() { };
		void draw();


	private:
		Vector3f position;
		Vector2f dimmensions;
		std::string text;
		const float* frameColor;
};

#endif /* SRC_GUI_TEXTINFRAME_H_ */
