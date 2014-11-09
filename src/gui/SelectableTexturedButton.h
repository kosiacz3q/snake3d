#ifndef SRC_GUI_SELECTABLETEXTUREDBUTTON_H_
#define SRC_GUI_SELECTABLETEXTUREDBUTTON_H_


#include "../Texture.h"
#include "../Colors.h"
#include "../Vectorf.h"

class SelectableTexturedButton
{
	public:
		SelectableTexturedButton(Vector3f posittion, Vector2f dimensions , std::string path,const float* selectionColor = Colors::Green);
		virtual ~SelectableTexturedButton();

		void setSelected(bool selected);
		bool isSelected();

		void draw();

	private:
		Texture* _texture;
		Vector3f _positon;
		Vector2f _dimensions;
		bool _isSelected;
		const float* _color;
};

#endif /* SRC_GUI_SELECTABLETEXTUREDBUTTON_H_ */
